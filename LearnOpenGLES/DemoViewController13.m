//
//  DemoViewController13.m
//  LearnOpenGLES
//
//  Created by apple on 2019/7/29.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController13.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"

@interface DemoViewController13 () <GLKViewDelegate>
{
    GLint filterPositionAttribute, filterTextureCoordinateAttribute;
    GLint filterInputTextureUniform;
    GLint alphaPositionAttribute, alphaTextureCoordinateAttribute;
    GLint alphaInputTextureUniform;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) GLProgram *program;

@property (nonatomic, strong) GLKTextureInfo *alphaTextureInfo;
@property (nonatomic, strong) GLProgram *alphaProgram;

@end

@implementation DemoViewController13

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    // shader
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_12" fragmentShaderFilename:@"shaderf_12"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"inputTextureCoordinate"];
    [self.program link];
    
    filterPositionAttribute = [self.program attributeIndex:@"position"];
    filterTextureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    filterInputTextureUniform = [self.program uniformIndex:@"inputImageTexture"]; // This does assume a name of "inputImageTexture" for the fragment shader
    
    self.alphaProgram = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_13" fragmentShaderFilename:@"shaderf_13"];
    [self.alphaProgram addAttribute:@"position"];
    [self.alphaProgram addAttribute:@"inputTextureCoordinate"];
    [self.alphaProgram link];
    
    alphaPositionAttribute = [self.alphaProgram attributeIndex:@"position"];
    alphaTextureCoordinateAttribute = [self.alphaProgram attributeIndex:@"inputTextureCoordinate"];
    alphaInputTextureUniform = [self.alphaProgram uniformIndex:@"inputImageTexture"]; // This does assume a name of "inputImageTexture" for the fragment shader
    
    // texture
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil]; // 将纹理坐标原点改为左下角（GLKit加载纹理，默认都是把坐标设置在“左上角”。然而，OpenGL的纹理贴图坐标却是在左下角，这样刚好颠倒）
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"for_test" ofType:@"jpg"];
    self.textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath options:options error:nil];
    
    NSString *alphaFilePath = [[NSBundle mainBundle] pathForResource:@"for_test_blend" ofType:@"png"];
    self.alphaTextureInfo = [GLKTextureLoader textureWithContentsOfFile:alphaFilePath options:options error:nil];
    
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
    static const GLfloat alphaImageVertices[] = {
        -0.5f, -0.5f, 0.0,
        0.5f, -0.5f, 0.0,
        -0.5f, 0.5f, 0.0,
        0.5f, 0.5f, 0.0,
    };
    static const GLfloat noRotationTextureCoordinates[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 启用着色器
    [self.program use];
    glEnableVertexAttribArray(filterPositionAttribute);
    glEnableVertexAttribArray(filterTextureCoordinateAttribute);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, self.textureInfo.name);
    glUniform1i(filterInputTextureUniform, 2);
    
    glVertexAttribPointer(filterPositionAttribute, 3, GL_FLOAT, 0, 0, imageVertices);
    glVertexAttribPointer(filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableVertexAttribArray(filterPositionAttribute);
    glDisableVertexAttribArray(filterTextureCoordinateAttribute);
    
    // GLES没有alpha测试，只能使用shader的discard关键字来实现
    // glEnable(GL_ALPHA_TEST); // 开启alpha测试
    // glAlphaFunc(GL_GEQUAL, 0.5f); // alpha大于等于0.5则通过（小于0.5则丢弃）
    
    // 启用着色器
    [self.alphaProgram use];
    glEnableVertexAttribArray(alphaPositionAttribute);
    glEnableVertexAttribArray(alphaTextureCoordinateAttribute);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, self.alphaTextureInfo.name);
    glUniform1i(alphaInputTextureUniform, 2);
    
    glVertexAttribPointer(alphaPositionAttribute, 3, GL_FLOAT, 0, 0, alphaImageVertices);
    glVertexAttribPointer(alphaTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableVertexAttribArray(alphaPositionAttribute);
    glDisableVertexAttribArray(alphaTextureCoordinateAttribute);
    
    // 关闭alpha测试
    // glDisable(GL_ALPHA_TEST);
}

- (void)dealloc
{
    [self.alphaProgram validate];
    self.alphaProgram = nil;
    [self.program validate];
    self.program = nil;
}

@end
