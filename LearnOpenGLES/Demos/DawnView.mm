//
//  DawnView.m
//  LearnOpenGLES
//
//  Created by apple on 2020/10/21.
//  Copyright © 2020 erpapa. All rights reserved.
//

#import "DawnView.h"
#include "webgpu.h"
#include <string.h>

/**
 * Vertex shader SPIR-V.
 * \code
 *    // glslc -Os -mfmt=num -o - -c in.vert
 *    #version 450
 *    layout(set = 0, binding = 0) uniform Rotation {
 *        float uRot;
 *    };
 *    layout(location = 0) in  vec2 aPos;
 *    layout(location = 1) in  vec3 aCol;
 *    layout(location = 0) out vec3 vCol;
 *    void main() {
 *        float cosA = cos(radians(uRot));
 *        float sinA = sin(radians(uRot));
 *        mat3 rot = mat3(cosA, sinA, 0.0,
 *                       -sinA, cosA, 0.0,
 *                        0.0,  0.0,  1.0);
 *        gl_Position = vec4(rot * vec3(aPos, 1.0), 1.0);
 *        vCol = aCol;
 *    }
 * \endcode
 */
static uint32_t const triangle_vert[] = {
    0x07230203, 0x00010000, 0x000d0008, 0x00000043, 0x00000000, 0x00020011, 0x00000001, 0x0006000b,
    0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001,
    0x0009000f, 0x00000000, 0x00000004, 0x6e69616d, 0x00000000, 0x0000002d, 0x00000031, 0x0000003e,
    0x00000040, 0x00050048, 0x00000009, 0x00000000, 0x00000023, 0x00000000, 0x00030047, 0x00000009,
    0x00000002, 0x00040047, 0x0000000b, 0x00000022, 0x00000000, 0x00040047, 0x0000000b, 0x00000021,
    0x00000000, 0x00050048, 0x0000002b, 0x00000000, 0x0000000b, 0x00000000, 0x00050048, 0x0000002b,
    0x00000001, 0x0000000b, 0x00000001, 0x00050048, 0x0000002b, 0x00000002, 0x0000000b, 0x00000003,
    0x00050048, 0x0000002b, 0x00000003, 0x0000000b, 0x00000004, 0x00030047, 0x0000002b, 0x00000002,
    0x00040047, 0x00000031, 0x0000001e, 0x00000000, 0x00040047, 0x0000003e, 0x0000001e, 0x00000000,
    0x00040047, 0x00000040, 0x0000001e, 0x00000001, 0x00020013, 0x00000002, 0x00030021, 0x00000003,
    0x00000002, 0x00030016, 0x00000006, 0x00000020, 0x0003001e, 0x00000009, 0x00000006, 0x00040020,
    0x0000000a, 0x00000002, 0x00000009, 0x0004003b, 0x0000000a, 0x0000000b, 0x00000002, 0x00040015,
    0x0000000c, 0x00000020, 0x00000001, 0x0004002b, 0x0000000c, 0x0000000d, 0x00000000, 0x00040020,
    0x0000000e, 0x00000002, 0x00000006, 0x00040017, 0x00000018, 0x00000006, 0x00000003, 0x00040018,
    0x00000019, 0x00000018, 0x00000003, 0x0004002b, 0x00000006, 0x0000001e, 0x00000000, 0x0004002b,
    0x00000006, 0x00000022, 0x3f800000, 0x00040017, 0x00000027, 0x00000006, 0x00000004, 0x00040015,
    0x00000028, 0x00000020, 0x00000000, 0x0004002b, 0x00000028, 0x00000029, 0x00000001, 0x0004001c,
    0x0000002a, 0x00000006, 0x00000029, 0x0006001e, 0x0000002b, 0x00000027, 0x00000006, 0x0000002a,
    0x0000002a, 0x00040020, 0x0000002c, 0x00000003, 0x0000002b, 0x0004003b, 0x0000002c, 0x0000002d,
    0x00000003, 0x00040017, 0x0000002f, 0x00000006, 0x00000002, 0x00040020, 0x00000030, 0x00000001,
    0x0000002f, 0x0004003b, 0x00000030, 0x00000031, 0x00000001, 0x00040020, 0x0000003b, 0x00000003,
    0x00000027, 0x00040020, 0x0000003d, 0x00000003, 0x00000018, 0x0004003b, 0x0000003d, 0x0000003e,
    0x00000003, 0x00040020, 0x0000003f, 0x00000001, 0x00000018, 0x0004003b, 0x0000003f, 0x00000040,
    0x00000001, 0x0006002c, 0x00000018, 0x00000042, 0x0000001e, 0x0000001e, 0x00000022, 0x00050036,
    0x00000002, 0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x00050041, 0x0000000e,
    0x0000000f, 0x0000000b, 0x0000000d, 0x0004003d, 0x00000006, 0x00000010, 0x0000000f, 0x0006000c,
    0x00000006, 0x00000011, 0x00000001, 0x0000000b, 0x00000010, 0x0006000c, 0x00000006, 0x00000012,
    0x00000001, 0x0000000e, 0x00000011, 0x0006000c, 0x00000006, 0x00000017, 0x00000001, 0x0000000d,
    0x00000011, 0x0004007f, 0x00000006, 0x00000020, 0x00000017, 0x00060050, 0x00000018, 0x00000023,
    0x00000012, 0x00000017, 0x0000001e, 0x00060050, 0x00000018, 0x00000024, 0x00000020, 0x00000012,
    0x0000001e, 0x00060050, 0x00000019, 0x00000026, 0x00000023, 0x00000024, 0x00000042, 0x0004003d,
    0x0000002f, 0x00000032, 0x00000031, 0x00050051, 0x00000006, 0x00000033, 0x00000032, 0x00000000,
    0x00050051, 0x00000006, 0x00000034, 0x00000032, 0x00000001, 0x00060050, 0x00000018, 0x00000035,
    0x00000033, 0x00000034, 0x00000022, 0x00050091, 0x00000018, 0x00000036, 0x00000026, 0x00000035,
    0x00050051, 0x00000006, 0x00000037, 0x00000036, 0x00000000, 0x00050051, 0x00000006, 0x00000038,
    0x00000036, 0x00000001, 0x00050051, 0x00000006, 0x00000039, 0x00000036, 0x00000002, 0x00070050,
    0x00000027, 0x0000003a, 0x00000037, 0x00000038, 0x00000039, 0x00000022, 0x00050041, 0x0000003b,
    0x0000003c, 0x0000002d, 0x0000000d, 0x0003003e, 0x0000003c, 0x0000003a, 0x0004003d, 0x00000018,
    0x00000041, 0x00000040, 0x0003003e, 0x0000003e, 0x00000041, 0x000100fd, 0x00010038
};

/**
 * Fragment shader SPIR-V.
 * \code
 *    // glslc -Os -mfmt=num -o - -c in.frag
 *    #version 450
 *    layout(location = 0) in  vec3 vCol;
 *    layout(location = 0) out vec4 fragColor;
 *    void main() {
 *        fragColor = vec4(vCol, 1.0);
 *    }
 * \endcode
 */
static uint32_t const triangle_frag[] = {
    0x07230203, 0x00010000, 0x000d0007, 0x00000013, 0x00000000, 0x00020011, 0x00000001, 0x0006000b,
    0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001,
    0x0007000f, 0x00000004, 0x00000004, 0x6e69616d, 0x00000000, 0x00000009, 0x0000000c, 0x00030010,
    0x00000004, 0x00000007, 0x00040047, 0x00000009, 0x0000001e, 0x00000000, 0x00040047, 0x0000000c,
    0x0000001e, 0x00000000, 0x00020013, 0x00000002, 0x00030021, 0x00000003, 0x00000002, 0x00030016,
    0x00000006, 0x00000020, 0x00040017, 0x00000007, 0x00000006, 0x00000004, 0x00040020, 0x00000008,
    0x00000003, 0x00000007, 0x0004003b, 0x00000008, 0x00000009, 0x00000003, 0x00040017, 0x0000000a,
    0x00000006, 0x00000003, 0x00040020, 0x0000000b, 0x00000001, 0x0000000a, 0x0004003b, 0x0000000b,
    0x0000000c, 0x00000001, 0x0004002b, 0x00000006, 0x0000000e, 0x3f800000, 0x00050036, 0x00000002,
    0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x0004003d, 0x0000000a, 0x0000000d,
    0x0000000c, 0x00050051, 0x00000006, 0x0000000f, 0x0000000d, 0x00000000, 0x00050051, 0x00000006,
    0x00000010, 0x0000000d, 0x00000001, 0x00050051, 0x00000006, 0x00000011, 0x0000000d, 0x00000002,
    0x00070050, 0x00000007, 0x00000012, 0x0000000f, 0x00000010, 0x00000011, 0x0000000e, 0x0003003e,
    0x00000009, 0x00000012, 0x000100fd, 0x00010038
};

@interface DawnView ()
{
    WGPUDevice _device;
    WGPUQueue _queue;
    WGPUSwapChain _swapchain;

    WGPURenderPipeline _pipeline;
    WGPUBuffer _vertBuf; // vertex buffer with triangle position and colours
    WGPUBuffer _indxBuf; // index buffer
    WGPUBuffer _uRotBuf; // uniform buffer (containing the rotation angle)
    WGPUBindGroup _bindGroup;
    
    float _rotDeg;
    CADisplayLink *_displayLink;
}

@end

@implementation DawnView

+ (Class)layerClass
{
    return [CAMetalLayer class];
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.contentScaleFactor = [UIScreen mainScreen].scale;
        self.layer.contentsScale = [UIScreen mainScreen].scale;
        uint32_t drawableWidth = frame.size.width * self.contentScaleFactor;
        uint32_t drawableHeight = frame.size.width * self.contentScaleFactor;
        webgpu::Handle handle = (__bridge webgpu::Handle)(self);
        _device = webgpu::create(handle, WGPUBackendType_Metal);
        _queue = wgpuDeviceGetDefaultQueue(_device);
        _swapchain = webgpu::createSwapChain(_device, drawableWidth, drawableHeight);
        [self createPipelineAndBuffers];
        [self startDisplayLink];
    }
    return self;
}

- (void)dealloc
{
    [self destory];
}

- (void)destory
{
    if (!_device) {
        return;
    }
    [self stopDisplayLink];
    wgpuBindGroupRelease(_bindGroup);
    _bindGroup = NULL;
    wgpuBufferRelease(_uRotBuf);
    _uRotBuf = NULL;
    wgpuBufferRelease(_indxBuf);
    _indxBuf = NULL;
    wgpuBufferRelease(_vertBuf);
    _vertBuf = NULL;
    wgpuRenderPipelineRelease(_pipeline);
    _pipeline = NULL;
    wgpuSwapChainRelease(_swapchain);
    _swapchain = NULL;
    wgpuQueueRelease(_queue);
    _queue = NULL;
    wgpuDeviceRelease(_device);
    _device = NULL;
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

/**
 * Helper to create a shader from SPIR-V IR.
 *
 * \param[in] code shader source (output using the \c -V \c -x options in \c glslangValidator)
 * \param[in] size size of \a code in bytes
 * \param[in] label optional shader name
 */
- (WGPUShaderModule)createShader:(const uint32_t *)code size:(uint32_t)size label:(const char * )label
{
    WGPUShaderModuleSPIRVDescriptor spirv = {};
    spirv.chain.sType = WGPUSType_ShaderModuleSPIRVDescriptor;
    spirv.codeSize = size / sizeof(uint32_t);
    spirv.code = code;
    WGPUShaderModuleDescriptor desc = {};
    desc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&spirv);
    desc.label = label;
    return wgpuDeviceCreateShaderModule(_device, &desc);
}

/**
 * Helper to create a buffer.
 *
 * \param[in] data pointer to the start of the raw data
 * \param[in] size number of bytes in \a data
 * \param[in] usage type of buffer
 */
- (WGPUBuffer)createBuffer:(const void *)data size:(size_t)size usage:(WGPUBufferUsage)usage
{
    WGPUBufferDescriptor desc = {};
    desc.usage = WGPUBufferUsage_CopyDst | usage;
    desc.size  = size;
    WGPUBuffer buffer = wgpuDeviceCreateBuffer(_device, &desc);
    wgpuQueueWriteBuffer(_queue, buffer, 0, data, size);
    return buffer;
}

/**
 * Bare minimum pipeline to draw a triangle using the above shaders.
 */
- (void)createPipelineAndBuffers
{
    // compile shaders
    WGPUShaderModule vertMod = [self createShader:triangle_vert size:sizeof(triangle_vert) label:NULL];
    WGPUShaderModule fragMod = [self createShader:triangle_frag size:sizeof(triangle_frag) label:NULL];

    // bind group layout (used by both the pipeline layout and uniform bind group, released at the end of this function)
    WGPUBindGroupLayoutEntry bglEntry = {};
    bglEntry.binding = 0;
    bglEntry.visibility = WGPUShaderStage_Vertex;
    bglEntry.type = WGPUBindingType_UniformBuffer;

    WGPUBindGroupLayoutDescriptor bglDesc = {};
    bglDesc.entryCount = 1;
    bglDesc.entries = &bglEntry;
    WGPUBindGroupLayout bindGroupLayout = wgpuDeviceCreateBindGroupLayout(_device, &bglDesc);

    // pipeline layout (used by the render pipeline, released after its creation)
    WGPUPipelineLayoutDescriptor layoutDesc = {};
    layoutDesc.bindGroupLayoutCount = 1;
    layoutDesc.bindGroupLayouts = &bindGroupLayout;
    WGPUPipelineLayout pipelineLayout = wgpuDeviceCreatePipelineLayout(_device, &layoutDesc);
    
    // begin pipeline set-up
    WGPURenderPipelineDescriptor desc = {};

    desc.layout = pipelineLayout;

    desc.vertexStage.module = vertMod;
    desc.vertexStage.entryPoint = "main";

    WGPUProgrammableStageDescriptor fragStage = {};
    fragStage.module = fragMod;
    fragStage.entryPoint = "main";
    desc.fragmentStage = &fragStage;

    // describe buffer layouts
    WGPUVertexAttributeDescriptor vertAttrs[2] = {};
    vertAttrs[0].format = WGPUVertexFormat_Float2;
    vertAttrs[0].offset = 0;
    vertAttrs[0].shaderLocation = 0;
    vertAttrs[1].format = WGPUVertexFormat_Float3;
    vertAttrs[1].offset = 2 * sizeof(float);
    vertAttrs[1].shaderLocation = 1;
    WGPUVertexBufferLayoutDescriptor vertDesc = {};
    vertDesc.arrayStride = 5 * sizeof(float);
    vertDesc.attributeCount = 2;
    vertDesc.attributes = vertAttrs;
    WGPUVertexStateDescriptor vertState = {};
#ifdef __EMSCRIPTEN__ // Emscripten hasn't yet caught up with the API changes
    vertState.indexFormat = WGPUIndexFormat_Uint16;
#endif
    vertState.vertexBufferCount = 1;
    vertState.vertexBuffers = &vertDesc;

    desc.vertexState = &vertState;
    desc.primitiveTopology = WGPUPrimitiveTopology_TriangleList;

    desc.sampleCount = 1;

    // describe blend
    WGPUBlendDescriptor blendDesc = {};
    blendDesc.operation = WGPUBlendOperation_Add;
    blendDesc.srcFactor = WGPUBlendFactor_SrcAlpha;
    blendDesc.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
    WGPUColorStateDescriptor colorDesc = {};
    colorDesc.format = webgpu::getSwapChainFormat(_device);
    colorDesc.alphaBlend = blendDesc;
    colorDesc.colorBlend = blendDesc;
    colorDesc.writeMask = WGPUColorWriteMask_All;

    desc.colorStateCount = 1;
    desc.colorStates = &colorDesc;

    desc.sampleMask = 0xFFFFFFFF; // <-- Note: this currently causes Emscripten to fail (sampleMask ends up as -1, which trips an assert)

    _pipeline = wgpuDeviceCreateRenderPipeline(_device, &desc);

    // partial clean-up (just move to the end, no?)
    wgpuPipelineLayoutRelease(pipelineLayout);

    wgpuShaderModuleRelease(fragMod);
    wgpuShaderModuleRelease(vertMod);

    // create the buffers (x, y, r, g, b)
    float const vertData[] = {
        -0.8f, -0.8f, 0.0f, 0.0f, 1.0f, // BL
         0.8f, -0.8f, 0.0f, 1.0f, 0.0f, // BR
        -0.0f,  0.8f, 1.0f, 0.0f, 0.0f, // top
    };
    uint16_t const indxData[] = {
        0, 1, 2,
        0 // padding (better way of doing this?)
    };
    _vertBuf = [self createBuffer:vertData size:sizeof(vertData) usage:WGPUBufferUsage_Vertex];
    _indxBuf = [self createBuffer:indxData size:sizeof(indxData) usage:WGPUBufferUsage_Index];

    // create the uniform bind group (note 'rotDeg' is copied here, not bound in any way)
    _uRotBuf = [self createBuffer:&_rotDeg size:sizeof(_rotDeg) usage:WGPUBufferUsage_Uniform];

    WGPUBindGroupEntry bgEntry = {};
    bgEntry.binding = 0;
    bgEntry.buffer = _uRotBuf;
    bgEntry.offset = 0;
    bgEntry.size = sizeof(_rotDeg);

    WGPUBindGroupDescriptor bgDesc = {};
    bgDesc.layout = bindGroupLayout;
    bgDesc.entryCount = 1;
    bgDesc.entries = &bgEntry;

    _bindGroup = wgpuDeviceCreateBindGroup(_device, &bgDesc);

    // last bit of clean-up
    wgpuBindGroupLayoutRelease(bindGroupLayout);
}

/**
 * Draws using the above pipeline and buffers.
 */
- (void)redraw
{
    WGPUTextureView backBufView = wgpuSwapChainGetCurrentTextureView(_swapchain);            // create textureView

    WGPURenderPassColorAttachmentDescriptor colorDesc = {};
    colorDesc.attachment = backBufView;
    colorDesc.loadOp  = WGPULoadOp_Clear;
    colorDesc.storeOp = WGPUStoreOp_Store;
    colorDesc.clearColor.r = 0.3f;
    colorDesc.clearColor.g = 0.3f;
    colorDesc.clearColor.b = 0.3f;
    colorDesc.clearColor.a = 1.0f;

    WGPURenderPassDescriptor renderPass = {};
    renderPass.colorAttachmentCount = 1;
    renderPass.colorAttachments = &colorDesc;

    WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(_device, nullptr);            // create encoder
    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPass);    // create pass

    // update the rotation
    _rotDeg += 0.1f;
    wgpuQueueWriteBuffer(_queue, _uRotBuf, 0, &_rotDeg, sizeof(_rotDeg));

    // draw the triangle (comment these five lines to simply clear the screen)
    wgpuRenderPassEncoderSetPipeline(pass, _pipeline);
    wgpuRenderPassEncoderSetBindGroup(pass, 0, _bindGroup, 0, 0);
    wgpuRenderPassEncoderSetVertexBuffer(pass, 0, _vertBuf, 0, 0);
#ifdef __EMSCRIPTEN__ // Emscripten hasn't yet caught up with the API changes
    wgpuRenderPassEncoderSetIndexBuffer(pass, indxBuf, 0, 0);
#else
    wgpuRenderPassEncoderSetIndexBufferWithFormat(pass, _indxBuf, WGPUIndexFormat_Uint16, 0, 0);
#endif
    wgpuRenderPassEncoderDrawIndexed(pass, 3, 1, 0, 0, 0);

    wgpuRenderPassEncoderEndPass(pass);
    wgpuRenderPassEncoderRelease(pass);                                                        // release pass
    WGPUCommandBuffer commands = wgpuCommandEncoderFinish(encoder, nullptr);                // create commands
    wgpuCommandEncoderRelease(encoder);                                                        // release encoder

    wgpuQueueSubmit(_queue, 1, &commands);
    wgpuCommandBufferRelease(commands);                                                        // release commands
#ifndef __EMSCRIPTEN__
    /*
     * TODO: wgpuSwapChainPresent is unsupported in Emscripten, so what do we do?
     */
    wgpuSwapChainPresent(_swapchain);
#endif
    wgpuTextureViewRelease(backBufView);                                                    // release textureView
}

@end
