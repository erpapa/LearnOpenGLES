//
//  DemoViewController12.m
//  LearnOpenGLES
//
//  Created by apple on 2019/7/29.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController12.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"

@interface DemoViewController12 () <GLKViewDelegate>
{
    GLint _filterPositionAttribute, _filterTextureCoordinateAttribute;
    GLint _filterInputTextureUniform;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) GLProgram *program;

@end

@implementation DemoViewController12

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
    
    _filterPositionAttribute = [self.program attributeIndex:@"position"];
    _filterTextureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    _filterInputTextureUniform = [self.program uniformIndex:@"inputImageTexture"]; // This does assume a name of "inputImageTexture" for the fragment shader
    
    // texture
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"for_test" ofType:@"jpg"];
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil]; // 将纹理坐标原点改为左下角（GLKit加载纹理，默认都是把坐标设置在“左上角”。然而，OpenGL的纹理贴图坐标却是在左下角，这样刚好颠倒）
    self.textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath options:options error:nil];
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
    static const GLfloat scissorImageVertices[] = {
        -0.25f, -0.25f, 0.0,
        0.25f, -0.25f, 0.0,
        -0.25f, 0.25f, 0.0,
        0.25f, 0.25f, 0.0,
    };
    static const GLfloat noRotationTextureCoordinates[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 启用着色器
    [self.program use];
    glEnableVertexAttribArray(_filterPositionAttribute);
    glEnableVertexAttribArray(_filterTextureCoordinateAttribute);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, self.textureInfo.name);
    glUniform1i(_filterInputTextureUniform, 2);
    
    glVertexAttribPointer(_filterPositionAttribute, 3, GL_FLOAT, 0, 0, imageVertices);
    glVertexAttribPointer(_filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableVertexAttribArray(_filterPositionAttribute);
    glDisableVertexAttribArray(_filterTextureCoordinateAttribute);
    
    // 裁剪测试只是在原来的视口标准的绘制区域内开辟一块矩形区域来显示，而不是把内容放到裁剪的区域内来显示。
    // 所以超出裁剪区域，之前绘制的内容不会受到影响
    // 开启裁剪测试
    glEnable(GL_SCISSOR_TEST);
    // 指定开辟的矩形区域
    CGRect scissorRect = CGRectInset(rect, 100, 100);
    glScissor(scissorRect.origin.x * view.contentScaleFactor, scissorRect.origin.y * view.contentScaleFactor, scissorRect.size.width * view.contentScaleFactor, scissorRect.size.height * view.contentScaleFactor);
    // 清除该区域内的颜色
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 在矩形局域内绘制内容
    // 启用着色器
    [self.program use];
    glEnableVertexAttribArray(_filterPositionAttribute);
    glEnableVertexAttribArray(_filterTextureCoordinateAttribute);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, self.textureInfo.name);
    glUniform1i(_filterInputTextureUniform, 2);
    
    glVertexAttribPointer(_filterPositionAttribute, 3, GL_FLOAT, 0, 0, scissorImageVertices);
    glVertexAttribPointer(_filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableVertexAttribArray(_filterPositionAttribute);
    glDisableVertexAttribArray(_filterTextureCoordinateAttribute);
    // 关闭裁剪测试
    glDisable(GL_SCISSOR_TEST);
}

@end
