//
//  DemoViewController3.m
//  LearnOpenGLES
//
//  Created by erpapa on 2018/2/7.
//  Copyright © 2018年 erpapa. All rights reserved.
//

#import "DemoViewController3.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"

static const GLfloat imageVertices[] = {
    -1.0f, -1.0f, 0.0,
    1.0f, -1.0f, 0.0,
    -1.0f, 1.0f, 0.0,
    1.0f, 1.0f, 0.0,
};

// 裁剪上下左右各0.2，得到中间0.6的区域
static const GLfloat noRotationTextureCoordinates[] = {
    0.2f, 0.2f,
    0.8f, 0.2f,
    0.2f, 0.8f,
    0.8f, 0.8f,
};

@interface DemoViewController3 () <GLKViewDelegate>
{
    GLint _filterPositionAttribute, _filterTextureCoordinateAttribute;
    GLint _filterInputTextureUniform;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) GLProgram *program;

@end

@implementation DemoViewController3

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
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_3" fragmentShaderFilename:@"shaderf_3"];
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
}

@end


