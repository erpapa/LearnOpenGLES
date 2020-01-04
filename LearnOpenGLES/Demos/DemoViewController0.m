//
//  DemoViewController0.m
//  LearnOpenGLES
//
//  Created by erpapa on 2018/2/7.
//  Copyright © 2018年 erpapa. All rights reserved.
//

#import "DemoViewController0.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"
#import "FilamentView.h"

static const GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0, // 左下
    1.0f, -1.0f, 0.0,  // 右下
    -1.0f,  1.0f, 0.0 // 左上
};

@interface DemoViewController0 () <GLKViewDelegate>
{
    GLint _filterPositionAttribute;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) GLProgram *program;
@property (nonatomic, strong) FilamentView *filamentView;

@end

@implementation DemoViewController0

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
//    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
//    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
//    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
//    self.glkView.delegate = self;
//    [self.view addSubview:self.glkView];
//    [EAGLContext setCurrentContext:self.eglContext];
//
//    // shader
//    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_0" fragmentShaderFilename:@"shaderf_0"];
//    [self.program addAttribute:@"position"]; // 把program的顶点属性索引与顶点shader中的变量名进行绑定
//    [self.program link]; // 创建可执行的 OpenGL ES program
//
//    _filterPositionAttribute = [self.program attributeIndex:@"position"]; // 获取program对象的参数值
//    [self.glkView display];
    
    self.filamentView = [[FilamentView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds))];
    [self.view addSubview:self.filamentView];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
//    glClearColor(0.5, 0.5, 0.5, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    [self.program use];
//    glEnableVertexAttribArray(_filterPositionAttribute);
//    glVertexAttribPointer(_filterPositionAttribute, 3, GL_FLOAT, 0, 0, vertices);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
//    glDisableVertexAttribArray(_filterPositionAttribute);
}

- (void)dealloc
{
    [self.filamentView destory];
}

@end

