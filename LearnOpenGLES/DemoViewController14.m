//
//  DemoViewController14.m
//  LearnOpenGLES
//
//  Created by apple on 2019/7/29.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController14.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"

@interface DemoViewController14 () <GLKViewDelegate>
{
    GLint filterPositionAttribute, filterTextureCoordinateAttribute;
    GLint filterInputTextureUniform;
    GLuint alphaTexture0, alphaTexture1;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) GLKTextureInfo *alphaTextureInfo;
@property (nonatomic, strong) GLProgram *program;

@end

@implementation DemoViewController14

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.backgroundColor = [UIColor clearColor];
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    // shader
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_14" fragmentShaderFilename:@"shaderf_14"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"inputTextureCoordinate"];
    [self.program link];
    
    filterPositionAttribute = [self.program attributeIndex:@"position"];
    filterTextureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    filterInputTextureUniform = [self.program uniformIndex:@"inputImageTexture"]; // This does assume a name of "inputImageTexture" for the fragment shader
    
    // texture
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil]; // 将纹理坐标原点改为左下角（GLKit加载纹理，默认都是把坐标设置在“左上角”。然而，OpenGL的纹理贴图坐标却是在左下角，这样刚好颠倒）
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"for_test" ofType:@"jpg"];
    self.textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath options:options error:nil];
    
    NSString *alphaFilePath = [[NSBundle mainBundle] pathForResource:@"for_test_blend" ofType:@"png"];
    self.alphaTextureInfo = [GLKTextureLoader textureWithContentsOfFile:alphaFilePath options:options error:nil];
    
    // 测试premultiply和unpremultiply
    uint8_t *textureData0 = malloc(sizeof(uint8_t) * 256 * 256 * 4);
    for (int i = 0; i < 256 * 256 * 4; i+=4) {
        textureData0[i + 0] = 127;
        textureData0[i + 1] = 127;
        textureData0[i + 2] = 0;
        textureData0[i + 3] = 64;
    }
    glGenTextures(1, &alphaTexture0);
    glBindTexture(GL_TEXTURE_2D, alphaTexture0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    free(textureData0);

    uint8_t *textureData1 = malloc(sizeof(uint8_t) * 256 * 256 * 4);
    for (int i = 0; i < 256 * 256 * 4; i+=4) {
        textureData0[i + 0] = 255;
        textureData0[i + 1] = 255;
        textureData0[i + 2] = 0;
        textureData0[i + 3] = 127;
    }
    glGenTextures(1, &alphaTexture1);
    glBindTexture(GL_TEXTURE_2D, alphaTexture1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    free(textureData1);
    
    [self.glkView display];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    static const GLfloat imageVertices[] = {
        -1.0f, -1.0f, 0.0,
        1.0f, -1.0f, 0.0,
        -1.0f, 1.0f, 0.0,
        1.0f, 1.0f, 0.0,
    };
    // 居中
    static const GLfloat alphaImageVertices[] = {
        -0.5f, -0.5f, 0.0,
        0.5f, -0.5f, 0.0,
        -0.5f, 0.5f, 0.0,
        0.5f, 0.5f, 0.0,
    };
    // 左下角
    static const GLfloat alphaCustomVertices0[] = {
        -1.0f, -1.0f, 0.0,
        0.0f, -1.0f, 0.0,
        -1.0f, 0.0f, 0.0,
        0.0f, 0.0f, 0.0,
    };
    // 右下角
    static const GLfloat alphaCustomVertices1[] = {
        0.0f, -1.0f, 0.0,
        1.0f, -1.0f, 0.0,
        0.0f, 0.0f, 0.0,
        1.0f, 0.0f, 0.0,
    };
    static const GLfloat noRotationTextureCoordinates[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    
    // glkView背景必须要设置为clearColor，才能透出glkView的父视图
    // 这样做的目的是为了让glkView与父视图做blend，这操作是借住系统自动完成的
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 启用着色器
//    [self.program use];
//    glEnableVertexAttribArray(filterPositionAttribute);
//    glEnableVertexAttribArray(filterTextureCoordinateAttribute);
//
//    glActiveTexture(GL_TEXTURE2);
//    glBindTexture(GL_TEXTURE_2D, self.textureInfo.name);
//    glUniform1i(filterInputTextureUniform, 2);
//
//    glVertexAttribPointer(filterPositionAttribute, 3, GL_FLOAT, 0, 0, imageVertices);
//    glVertexAttribPointer(filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//
//    glDisableVertexAttribArray(filterPositionAttribute);
//    glDisableVertexAttribArray(filterTextureCoordinateAttribute);
    
    // 开启blend混合模式
    glEnable(GL_BLEND);
    // 启用着色器
    [self.program use];
    glEnableVertexAttribArray(filterPositionAttribute);
    glEnableVertexAttribArray(filterTextureCoordinateAttribute);
    
    // 预乘alpha（premultiply）
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    // 没有预乘alpha（unpremultiply）
    // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, self.alphaTextureInfo.name);
    glUniform1i(filterInputTextureUniform, 2);

    glVertexAttribPointer(filterPositionAttribute, 3, GL_FLOAT, 0, 0, alphaImageVertices);
    glVertexAttribPointer(filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    // 预乘alpha（premultiply）
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, alphaTexture0);
    glUniform1i(filterInputTextureUniform, 2);
    
    glVertexAttribPointer(filterPositionAttribute, 3, GL_FLOAT, 0, 0, alphaCustomVertices0);
    glVertexAttribPointer(filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    // 没有预乘alpha（unpremultiply）
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, alphaTexture1);
    glUniform1i(filterInputTextureUniform, 2);
    
    glVertexAttribPointer(filterPositionAttribute, 3, GL_FLOAT, 0, 0, alphaCustomVertices1);
    glVertexAttribPointer(filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableVertexAttribArray(filterPositionAttribute);
    glDisableVertexAttribArray(filterTextureCoordinateAttribute);
    // 关闭blend混合模式
    glDisable(GL_BLEND);
    
    /**
     * 可以得出结论：
     * 1.texture预乘，使用glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
     * 公式为：
     *      COLOR(rgb) = SRC(rgb) + DST(rgb) * (1 - SRC(a));
     *      COLOR(a) = SRC(a) + DST(a) * (1 - SRC(a));
     * 2.texture未预乘，使用glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
     * 公式为：
     *      COLOR(rgb) = SRC(rgb) * SRC(a) + DST(rgb) * (1 - SRC(a));
     *      COLOR(a) = SRC(a) + DST(a) * (1 - SRC(a));
     *
     * ##############################################################
     *
     * 不要使用glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)：
     * 1.texture预乘，会导致rgba多乘一次alpha
     * 公式为：
     *      COLOR(rgb) = SRC(rgb) * SRC(a) + DST(rgb) * (1 - SRC(a));
     *      COLOR(a) = SRC(a) * SRC(a) + DST(a) * (1 - SRC(a));
     * 2.texture未预乘，会导致a多乘一次alpha
     * 公式为：
     *      COLOR(rgb) = SRC(rgb) * SRC(a) + DST(rgb) * (1 - SRC(a));
     *      COLOR(a) = SRC(a) * SRC(a) + DST(a) * (1 - SRC(a));
     *
     * 多乘一次alpha会导致当前结果的a减小，再用来做blend的时候，颜色比例不对，
     * 在COLOR(rgb) = SRC(rgb) + DST(rgb) * (1 - SRC(a))这个公式中，
     * 当前结果的a减小，(1 - SRC(a))变大了，导致颜色整体偏向背景色。
     **/
}

- (void)dealloc
{
    [self.program validate];
    self.program = nil;
    
    if (alphaTexture0) {
        glDeleteTextures(1, &alphaTexture0);
        alphaTexture0 = 0;
    }
    if (alphaTexture1) {
        glDeleteTextures(1, &alphaTexture1);
        alphaTexture1 = 0;
    }
}


@end
