/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "FilamentView.h"
#import <GLKit/GLKit.h>
#import <MoltenVKGLSLToSPIRVConverter/GLSLConversion.h>
#import <MoltenVKSPIRVToMSLConverter/SPIRVConversion.h>
#import "GPUImagePicture.h"
#include <backend/Platform.h>
#include "private/backend/CommandStream.h"
#include "private/backend/CommandBufferQueue.h"
#define FILAMENT_USE_METAL 1

#if FILAMENT_USE_METAL

NSString *const kVertexShaderString = @"#version 450\n\
layout(set = 0, binding = 0) uniform ModelMatrix {\n\
    mat4 modelMatrix;\n\
};\n\
layout(location = 0) in vec3 aPos;\n\
layout(location = 1) in vec4 aColor;\n\
layout(location = 2) in vec2 aCoord;\n\
layout(location = 0) out vec4 vColor;\n\
layout(location = 1) out vec2 vCoord;\n\
void main() {\n\
    gl_Position = modelMatrix * vec4(aPos, 1.0);\n\
    vColor = aColor;\n\
    vCoord = aCoord;\n\
}\n\
";

NSString *const kFragmentShaderString = @"#version 450\n\
layout(location = 0) in vec4 vColor;\n\
layout(location = 1) in vec2 vCoord;\n\
layout(location = 0) out vec4 fragColor;\n\
layout(binding = 0) uniform sampler2D imageTexture;\n\
void main() {\n\
    vec4 imageColor = texture(imageTexture, vCoord);\n\
    fragColor = vec4(imageColor.r, imageColor.g, imageColor.b, vColor.a);\n\
}\n\
";

#else

NSString *const kVertexShaderString = @"#version 300 es\n\
precision mediump float;\n\
layout (std140) uniform ModelMatrix {\n\
    mat4 modelMatrix;\n\
};\n\
layout(location = 0) in vec3 aPos;\n\
layout(location = 1) in vec4 aColor;\n\
layout(location = 2) in vec2 aCoord;\n\
layout(location = 0) out vec4 vColor;\n\
layout(location = 1) out vec2 vCoord;\n\
void main() {\n\
    gl_Position = modelMatrix * vec4(aPos, 1.0);\n\
    vColor = aColor;\n\
    vCoord = aCoord;\n\
}\n\
";

NSString *const kFragmentShaderString = @"#version 300 es\n\
precision mediump float;\n\
layout(location = 0) in vec4 vColor;\n\
layout(location = 1) in vec2 vCoord;\n\
layout(location = 0) out vec4 fragColor;\n\
uniform sampler2D imageTexture;\n\
void main() {\n\
    vec4 imageColor = texture(imageTexture, vCoord);\n\
    fragColor = vec4(imageColor.r, imageColor.g, imageColor.b, vColor.a);\n\
}\n\
";

#endif

void FreeBufferCallback(void* buffer, size_t size, void* user)
{
    free(buffer);
}

@interface FilamentView ()
{
    filament::backend::Backend _backend;
    filament::backend::Platform *_platform;
    filament::backend::Driver *_driver;
    filament::backend::CommandBufferQueue *_command_buffer_queue;
    
    filament::backend::DriverApi _driverApi;
    filament::backend::SwapChainHandle _swap_chain;
    filament::backend::RenderTargetHandle _render_target;
    filament::backend::UniformBufferHandle _uniform_buffer;
    
    filament::backend::TextureHandle _texture;
    filament::backend::SamplerParams _sampler;
    filament::backend::SamplerGroupHandle _sampler_group;
    
    filament::backend::VertexBufferHandle _vertexBuffer;
    filament::backend::IndexBufferHandle _indexBuffer;
    filament::backend::RenderPrimitiveHandle _primitive;
    
    filament::backend::PipelineState _pipeline;
    
    uint32_t _frame_id;
    uint32_t _drawable_width;
    uint32_t _drawable_height;
    dispatch_queue_t _driver_queue;
    float _rotationDegree;
    GLKMatrix4 _modelMatrix;
    CADisplayLink *_displayLink;
    GPUImagePicture *_picture;
}
@end

@implementation FilamentView

+ (Class)layerClass
{
#if FILAMENT_USE_METAL
    return [CAMetalLayer class];
#else
    return [CAEAGLLayer class];
#endif
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.contentScaleFactor = [UIScreen mainScreen].scale;
        self.layer.contentsScale = [UIScreen mainScreen].scale;
        _drawable_width = frame.size.width * self.contentScaleFactor;
        _drawable_height = frame.size.height * self.contentScaleFactor;
        _driver_queue = dispatch_queue_create("com.erpapa.FilamentView.queue", DISPATCH_QUEUE_SERIAL);
        [self setupLayer];
        [self setupAndExecute];
        [self startDisplayLink];
    }
    return self;
}

- (void)setupLayer
{
#if FILAMENT_USE_METAL
    CAMetalLayer *metalLayer = (CAMetalLayer *)self.layer;
    metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    metalLayer.drawableSize = CGSizeMake(_drawable_width, _drawable_height);
    _backend = filament::backend::Backend::METAL;
#else
    CAEAGLLayer *glLayer = (CAEAGLLayer *)self.layer;
    glLayer.opaque = YES;
    glLayer.drawableProperties = @
    {
        kEAGLDrawablePropertyRetainedBacking : @(NO),
        kEAGLDrawablePropertyColorFormat : kEAGLColorFormatRGBA8,
    };
    _backend = filament::backend::Backend::OPENGL;
#endif
}

- (void)setupAndExecute
{
    dispatch_sync(_driver_queue, ^{
        [self setupPlatform];
        [self setupPipeline];
        [self setupUbo];
        [self setupTexture];
        [self setupPrimitive];
    });
    dispatch_async(_driver_queue, ^{
        while (true)
        {
            if (![self execute])
            {
                break;
            }
        }
        _driverApi.terminate();
    });
}

- (void)setupPlatform
{
    _platform = filament::backend::DefaultPlatform::create(&_backend);
    _driver = _platform->createDriver(nullptr);
    _command_buffer_queue = new filament::backend::CommandBufferQueue(1024 * 1024, 1024 * 1024 * 3);
    _driverApi = filament::backend::CommandStream(*_driver, _command_buffer_queue->getCircularBuffer());
    _swap_chain = _driverApi.createSwapChain((__bridge void *)self.layer, 0);
    _render_target = _driverApi.createDefaultRenderTarget();
}

- (void)setupPipeline
{
    NSData *vsData = nil;
    NSData *fsData = nil;
    if (_backend == filament::backend::Backend::METAL) {
        NSData *vertexData = [self glslToSpirv:kVertexShaderString type:filament::backend::Program::Shader::VERTEX];
        NSData *fragmentData = [self glslToSpirv:kFragmentShaderString type:filament::backend::Program::Shader::FRAGMENT];
        NSString *vertexMSL = [self spirvToMSL:vertexData];
        NSString *fragmentMSL = [self spirvToMSL:fragmentData];
        vsData = [vertexMSL dataUsingEncoding:NSUTF8StringEncoding];
        fsData = [fragmentMSL dataUsingEncoding:NSUTF8StringEncoding];
    } else {
        vsData = [kVertexShaderString dataUsingEncoding:NSUTF8StringEncoding];
        fsData = [kFragmentShaderString dataUsingEncoding:NSUTF8StringEncoding];
    }
    filament::backend::Program pb;
    pb.diagnostics(utils::CString("triangle"))
      .withVertexShader(vsData.bytes, vsData.length)
      .withFragmentShader(fsData.bytes, fsData.length);
    // bind ubo
    pb.setUniformBlock(0, utils::CString("ModelMatrix"));
    // bind texture
    filament::backend::Program::Sampler samplers[1];
    samplers[0].name = utils::CString("imageTexture");
    samplers[0].binding = 0;
    pb.setSamplerGroup(0, samplers, 1);
    _pipeline.program = _driverApi.createProgram(std::move(pb));
    _pipeline.rasterState.culling = filament::backend::CullingMode::NONE;
    _pipeline.rasterState.depthFunc = filament::backend::SamplerCompareFunc::LE;
    _pipeline.rasterState.depthWrite = true;
    _pipeline.rasterState.colorWrite = true;
    // blend
    // _pipeline.rasterState.blendFunctionSrcRGB = filament::backend::BlendFunction::SRC_ALPHA;
    // _pipeline.rasterState.blendFunctionSrcAlpha = filament::backend::BlendFunction::ONE_MINUS_SRC_ALPHA;
    // _pipeline.rasterState.blendFunctionDstRGB = filament::backend::BlendFunction::ONE;
    // _pipeline.rasterState.blendFunctionDstAlpha = filament::backend::BlendFunction::ONE_MINUS_SRC_ALPHA;
    // scissor
    _pipeline.scissor.left = 0;
    _pipeline.scissor.bottom = 0;
    _pipeline.scissor.width = _drawable_width;
    _pipeline.scissor.height = _drawable_height;
}

- (void)setupUbo
{
    _modelMatrix = GLKMatrix4Identity;
    _uniform_buffer = _driverApi.createUniformBuffer(sizeof(_modelMatrix), filament::backend::BufferUsage::DYNAMIC);
    void *matrix_buffer = _driverApi.allocate(sizeof(_modelMatrix));
    memcpy(matrix_buffer, &_modelMatrix, sizeof(_modelMatrix));
    _driverApi.loadUniformBuffer(_uniform_buffer, filament::backend::BufferDescriptor(matrix_buffer, sizeof(_modelMatrix)));
}

- (void)setupTexture
{
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"for_test" ofType:@"jpg"];
    UIImage *image = [UIImage imageWithContentsOfFile:filePath];
    _picture = [[GPUImagePicture alloc] initWithImage:image];
    int texture_width = _picture.pixelSizeOfImage.width;
    int texture_height = _picture.pixelSizeOfImage.height;
    int texture_data_size = texture_width * texture_height * 4;
    _sampler_group = _driverApi.createSamplerGroup(1);
    _texture = _driverApi.createTexture(filament::backend::SamplerType::SAMPLER_2D, 1, filament::backend::TextureFormat::RGBA8, 1, texture_width, texture_height, 1, filament::backend::TextureUsage::COLOR_ATTACHMENT);
    _sampler.filterMin = filament::backend::SamplerMinFilter::NEAREST;
    _sampler.filterMag = filament::backend::SamplerMagFilter::NEAREST;
    _sampler.wrapS = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
    _sampler.wrapT = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
    _sampler.wrapR = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
    auto data = filament::backend::PixelBufferDescriptor(_picture.data, texture_data_size, filament::backend::PixelDataFormat::RGBA, filament::backend::PixelDataType::UBYTE,
        nullptr); // FreeBufferCallback
    _driverApi.update2DImage(_texture, 0, 0, 0, texture_width, texture_height, std::move(data));
    filament::backend::SamplerGroup samplers(1);
    samplers.setSampler(0, _texture, _sampler);
    _driverApi.updateSamplerGroup(_sampler_group, std::move(samplers));
}

- (void)setupPrimitive
{
    int attributeCount = 3;
    uint32_t enabledAttributes = (1 << 0) | (1 << 1) | (1 << 2);
    filament::backend::AttributeArray attributes;
    attributes[0].offset = 0;
    attributes[0].stride = sizeof(float) * 9;
    attributes[0].buffer = 0;
    attributes[0].type = filament::backend::ElementType::FLOAT3;
    attributes[1].offset = sizeof(float) * 3;
    attributes[1].stride = sizeof(float) * 9;
    attributes[1].buffer = 0;
    attributes[2].type = filament::backend::ElementType::FLOAT4;
    attributes[2].offset = sizeof(float) * 7;
    attributes[2].stride = sizeof(float) * 9;
    attributes[2].buffer = 0;
    attributes[2].type = filament::backend::ElementType::FLOAT2;
    float const vertexData[] = {
        -0.8f, -0.8f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   0.0, 0.0, // BL
         0.8f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,   1.0, 0.0, // BR
        -0.8f,  0.8f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,   0.0, 1.0, // tl
         0.8f,  0.8f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0, 1.0  // tr
    };
    uint16_t const indexData[] = {0, 1, 2, 2, 1, 3};
    void *vertex_buffer = malloc(sizeof(vertexData));
    memcpy(vertex_buffer, &vertexData[0], sizeof(vertexData));
    _vertexBuffer = _driverApi.createVertexBuffer(1, attributeCount, 4, attributes, filament::backend::BufferUsage::DYNAMIC);
    _driverApi.updateVertexBuffer(_vertexBuffer, 0, filament::backend::BufferDescriptor(vertex_buffer, sizeof(vertexData), FreeBufferCallback), 0);
    void *index_buffer = malloc(sizeof(indexData));
    memcpy(index_buffer, &indexData[0], sizeof(indexData));
    _indexBuffer = _driverApi.createIndexBuffer(filament::backend::ElementType::USHORT, 6, filament::backend::BufferUsage::DYNAMIC);
    _driverApi.updateIndexBuffer(_indexBuffer, filament::backend::BufferDescriptor(index_buffer, sizeof(indexData), FreeBufferCallback), 0);
    _primitive = _driverApi.createRenderPrimitive();
    _driverApi.setRenderPrimitiveBuffer(_primitive, _vertexBuffer, _indexBuffer, enabledAttributes);
    _driverApi.setRenderPrimitiveRange(_primitive, filament::backend::PrimitiveType::TRIANGLES, 0, 0, 3, 6);
}

- (void)dealloc
{
    [self destory];
}

- (void)pause
{
    _displayLink.paused = YES;
}

- (void)resume
{
    _displayLink.paused = NO;
}

- (void)destory
{
    if (!_platform) {
        return;
    }
    // 注意代码调用顺序
    [self stopDisplayLink];
    [self destoryDriver];
    [self flush];
    _command_buffer_queue->requestExit();
    dispatch_sync(_driver_queue, ^{
        delete _command_buffer_queue;
        _command_buffer_queue = nullptr;
        delete _driver;
        _driver = nullptr;
        delete _platform;
        _platform = nullptr;
    });
}

- (void)destoryDriver
{
    _driverApi.destroyRenderTarget(_render_target);
    _render_target.clear();
    _driverApi.destroySwapChain(_swap_chain);
    _swap_chain.clear();
    _driverApi.destroyProgram(_pipeline.program);
    _pipeline.program.clear();
    _driverApi.destroyUniformBuffer(_uniform_buffer);
    _uniform_buffer.clear();
    _driverApi.destroySamplerGroup(_sampler_group);
    _sampler_group.clear();
    _driverApi.destroyTexture(_texture);
    _texture.clear();
    _driverApi.destroyVertexBuffer(_vertexBuffer);
    _vertexBuffer.clear();
    _driverApi.destroyIndexBuffer(_indexBuffer);
    _indexBuffer.clear();
    _driverApi.destroyRenderPrimitive(_primitive);
    _primitive.clear();
}

- (void)startDisplayLink
{
    [self stopDisplayLink];
    _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(redraw)];
    _displayLink.preferredFramesPerSecond = 60;
    [_displayLink addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void)stopDisplayLink
{
    [_displayLink invalidate];
    _displayLink = nil;
}

- (void)beginFrame
{
    _frame_id++;
    int64_t monotonic_clock_ns(std::chrono::steady_clock::now().time_since_epoch().count());
    _driverApi.makeCurrent(_swap_chain, _swap_chain);
    _driverApi.beginFrame(monotonic_clock_ns, _frame_id, NULL, nullptr);
}

- (void)render
{
    // buffer
    _rotationDegree += 0.1;
    _modelMatrix = GLKMatrix4MakeRotation(GLKMathDegreesToRadians(_rotationDegree), 0, 0, 1);
    void *matrix_buffer = _driverApi.allocate(sizeof(_modelMatrix));
    memcpy(matrix_buffer, &_modelMatrix, sizeof(_modelMatrix));
    _driverApi.loadUniformBuffer(_uniform_buffer, filament::backend::BufferDescriptor(matrix_buffer, sizeof(_modelMatrix)));
    // params
    filament::backend::RenderPassParams params;
    params.flags.clear = filament::backend::TargetBufferFlags::COLOR;
    params.flags.discardStart = filament::backend::TargetBufferFlags::NONE;
    params.flags.discardEnd = filament::backend::TargetBufferFlags::NONE;
    params.viewport.left = 0;
    params.viewport.bottom = 0;
    params.viewport.width = _drawable_width;
    params.viewport.height = _drawable_height;
    params.clearColor = {0.1, 0.2, 0.3, 1.0};
    // render
    _driverApi.beginRenderPass(_render_target, params);
    _driverApi.bindUniformBuffer(0, _uniform_buffer);
    _driverApi.bindSamplers(0, _sampler_group);
    _driverApi.draw(_pipeline, _primitive);
    _driverApi.endRenderPass();
    _driverApi.flush();
}

- (void)endFrame
{
    _driverApi.commit(_swap_chain);
    _driverApi.endFrame(_frame_id);
    [self flush];
}

- (void)flush
{
    _driver->purge();
    _command_buffer_queue->flush();
}

- (BOOL)execute
{
    auto buffers = _command_buffer_queue->waitForCommands();
    if (buffers.empty())
    {
        return NO;
    }

    for (int i = 0; i < buffers.size(); ++i)
    {
        auto& item = buffers[i];
        if (item.begin)
        {
            _driverApi.execute(item.begin);
            _command_buffer_queue->releaseBuffer(item);
        }
    }
    return YES;
}

- (void)redraw
{
    [self beginFrame];
    [self render];
    [self endFrame];
}

#pragma mark - Convert

- (NSData *)glslToSpirv:(NSString *)glsl type:(filament::backend::Program::Shader)type
{
    MVKShaderStage stage;
    switch (type)
    {
        case filament::backend::Program::Shader::VERTEX:
            stage = kMVKShaderStageVertex;
            break;
        case filament::backend::Program::Shader::FRAGMENT:
            stage = kMVKShaderStageFragment;
            break;
        default:
            stage = kMVKShaderStageAuto;
            break;
    }
    uint32_t *spirv_code = NULL;
    size_t size = 0;
    char *log = NULL;
    bool success = mvkConvertGLSLToSPIRV(glsl.UTF8String,
                                         stage,
                                         &spirv_code,
                                         &size,
                                         &log,
                                         true,
                                         true);
    if (!success)
    {
        NSLog(@"shader compile error: %s", log);
    }
    void *spirv_data = malloc(size);
    memcpy(spirv_data, spirv_code, size);
    NSData *data = [NSData dataWithBytesNoCopy:spirv_data length:size freeWhenDone:YES];
    free(log);
    free(spirv_code);
    return data;
}

- (NSString *)spirvToMSL:(NSData *)spirv
{
    char *msl_code = NULL;
    char *log = NULL;
    bool success = mvkConvertSPIRVToMSL((uint32_t *)spirv.bytes, (size_t)(spirv.length / 4), &msl_code, &log, true, true);
    if (!success)
    {
        NSLog(@"shader compile error: %s", log);
    }
    NSString *msl = [NSString stringWithCString:msl_code encoding:NSUTF8StringEncoding];
    free(log);
    free(msl_code);
    return msl;
}

@end
