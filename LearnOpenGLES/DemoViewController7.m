//
//  DemoViewController7.m
//  LearnOpenGLES
//
//  Created by apple on 2018/11/1.
//  Copyright © 2018 erpapa. All rights reserved.
//

#import "DemoViewController7.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import "GLProgram.h"
#include "sphere.h"

static const GLfloat imageVertices[] = {
    -1.0f, -1.0f, 0.0,
    1.0f, -1.0f, 0.0,
    -1.0f, 1.0f, 0.0,
    1.0f, 1.0f, 0.0,
};

static const GLfloat noRotationTextureCoordinates[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
};

@interface DemoViewController7 () <GLKViewDelegate>
{
    GLuint _VAO, _VBO0, _VBO1, _VAO1, _VBO10, _VBO11;
    GLint _positionAttribute, _textureCoordinateAttribute;
    GLKMatrix4 _sunModelMatrix, _earthModelMatrix, _moonModelMatrix, _orbitModelMatrix;
    GLKMatrix4 _viewMatrix, _projectionMatrix;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *sunInfo;
@property (nonatomic, strong) GLKTextureInfo *earthInfo;
@property (nonatomic, strong) GLKTextureInfo *moonInfo;
@property (nonatomic, strong) GLKTextureInfo *orbitInfo;
@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) GLProgram *program;

@property (nonatomic, assign) float sunDegree; // 太阳自转
@property (nonatomic, assign) float earthDegree; // 地球自转
@property (nonatomic, assign) float earthRevolution; // 地球公转
@property (nonatomic, assign) float moonDegree; // 月球自转
@property (nonatomic, assign) float moonRevolution; // 月球公转

@end

@implementation DemoViewController7

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    // shader
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_7" fragmentShaderFilename:@"shaderf_7"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"inputTextureCoordinate"];
    [self.program link];
    
    // 顶点
    _positionAttribute = [self.program attributeIndex:@"position"];
    _textureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    // 轨道VAO
    {
        // 创建索引缓冲对象
        glGenVertexArraysOES(1, &_VAO);
        glGenBuffers(1, &_VBO0);
        glGenBuffers(1, &_VBO1);
        
        // 绑定VAO
        glBindVertexArrayOES(_VAO);
        
        // 把顶点数组复制到缓冲中供OpenGL使用
        glBindBuffer(GL_ARRAY_BUFFER, _VBO0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(imageVertices), imageVertices, GL_STATIC_DRAW);
        // 位置属性
        glEnableVertexAttribArray(_positionAttribute);
        glVertexAttribPointer(_positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        
        // 把顶点数组复制到缓冲中供OpenGL使用
        glBindBuffer(GL_ARRAY_BUFFER, _VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(noRotationTextureCoordinates), noRotationTextureCoordinates, GL_STATIC_DRAW);
        // 纹理
        glEnableVertexAttribArray(_textureCoordinateAttribute);
        glVertexAttribPointer(_textureCoordinateAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        
        // glBindBuffer(GL_ARRAY_BUFFER, 0); // 不可以解绑，此时VAO管理着它们
        glBindVertexArrayOES(0); // 解绑VAO（这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法）
    }
    // 球体VAO
    {
        // 创建索引缓冲对象
        glGenVertexArraysOES(1, &_VAO1);
        glGenBuffers(1, &_VBO10);
        glGenBuffers(1, &_VBO11);
        
        // 绑定VAO1
        glBindVertexArrayOES(_VAO1);
        
        // 把顶点数组复制到缓冲中供OpenGL使用
        glBindBuffer(GL_ARRAY_BUFFER, _VBO10);
        glBufferData(GL_ARRAY_BUFFER, sizeof(sphereVerts), sphereVerts, GL_STATIC_DRAW);
        // 位置属性
        glEnableVertexAttribArray(_positionAttribute);
        glVertexAttribPointer(_positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        
        // 把顶点数组复制到缓冲中供OpenGL使用
        glBindBuffer(GL_ARRAY_BUFFER, _VBO11);
        glBufferData(GL_ARRAY_BUFFER, sizeof(sphereTexCoords), sphereTexCoords, GL_STATIC_DRAW);
        // 纹理
        glEnableVertexAttribArray(_textureCoordinateAttribute);
        glVertexAttribPointer(_textureCoordinateAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        
        // glBindBuffer(GL_ARRAY_BUFFER, 0); // 不可以解绑，此时VAO管理着它们
        glBindVertexArrayOES(0); // 解绑VAO（这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法）
    }
    
    // texture
    NSString *sunFilePath = [[NSBundle mainBundle] pathForResource:@"sun" ofType:@"jpg"];
    self.sunInfo = [GLKTextureLoader textureWithContentsOfFile:sunFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    NSString *earthFilePath = [[NSBundle mainBundle] pathForResource:@"earth_diffuse" ofType:@"jpg"];
    self.earthInfo = [GLKTextureLoader textureWithContentsOfFile:earthFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    NSString *moonFilePath = [[NSBundle mainBundle] pathForResource:@"moon" ofType:@"jpg"];
    self.moonInfo = [GLKTextureLoader textureWithContentsOfFile:moonFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    NSString *orbitFilePath = [[NSBundle mainBundle] pathForResource:@"orbit" ofType:@"png"];
    self.orbitInfo = [GLKTextureLoader textureWithContentsOfFile:orbitFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    
    // 初始化模型矩阵
    _sunModelMatrix = GLKMatrix4Identity;
    _earthModelMatrix = GLKMatrix4Identity;
    _moonModelMatrix = GLKMatrix4Identity;
    _orbitModelMatrix = GLKMatrix4Identity;
    // 设置摄像机在(0，3.0，9.0)坐标，看向(0，0，0)点。Y轴正向为摄像机顶部指向的方向
    _viewMatrix = GLKMatrix4MakeLookAt(0.0, 3.0, 9.0, 0, 0, 0, 0, 1, 0);
    // 使用透视投影矩阵，视场角设置为90°
    _projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90.0f), 1.0f, 0.1f, 100.0f);
    // 正交投影矩阵
    // _projectionMatrix = GLKMatrix4MakeOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    
    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
    [self.displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [self.displayLink invalidate];
    self.displayLink = nil;
}

- (void)update
{
    // 太阳
    {
        // 缩放
        GLKMatrix4 scale = GLKMatrix4MakeScale(3.6, 3.6, 3.6);
        // 太阳自转
        float radians = GLKMathDegreesToRadians(self.sunDegree);
        GLKMatrix4 rotation = GLKMatrix4MakeRotation(radians, 0.0, 1.0, 0.0);
        _sunModelMatrix = GLKMatrix4Multiply(rotation, scale);
    }
    // 地球
    {
        // 缩放
        GLKMatrix4 scale = GLKMatrix4MakeScale(1.2, 1.2, 1.2);
        // 地球自转
        float radians = GLKMathDegreesToRadians(self.earthDegree);
        GLKMatrix4 rotation = GLKMatrix4MakeRotation(radians, 0.0, 1.0, 0.0);
        // 地球公转
        float earthRevolution = GLKMathDegreesToRadians(self.earthRevolution);
        GLKMatrix4 earthTranslation = GLKMatrix4MakeTranslation(6.0 * sinf(earthRevolution), 0.0, 6.0 * cosf(earthRevolution));
        _earthModelMatrix = GLKMatrix4Multiply(GLKMatrix4Multiply(earthTranslation, rotation), scale);
        _orbitModelMatrix = GLKMatrix4Multiply(GLKMatrix4MakeRotation(GLKMathDegreesToRadians(90.0), 1.0, 0.0, 0.0), GLKMatrix4MakeScale(6.25, 6.25, 1.0));
    }
    // 月球
    {
        // 缩放
        GLKMatrix4 scale = GLKMatrix4MakeScale(0.5, 0.5, 0.5);
        // 月球自转
        float radians = GLKMathDegreesToRadians(self.moonDegree);
        GLKMatrix4 rotation = GLKMatrix4MakeRotation(radians, 0.0, 1.0, 0.0);
        // 月球公转(绕地球旋转)
        // 计算地球公转
        float earthRevolution = GLKMathDegreesToRadians(self.earthRevolution);
        GLKMatrix4 earthTranslation = GLKMatrix4MakeTranslation(6.0 * sinf(earthRevolution), 0.0, 6.0 * cosf(earthRevolution));
        // 计算月球公转
        float moonRevolution = GLKMathDegreesToRadians(self.moonRevolution);
        GLKMatrix4 moonTranslation = GLKMatrix4MakeTranslation(1.2 * sinf(moonRevolution), 0.0, 1.2 * cosf(moonRevolution));
        _moonModelMatrix = GLKMatrix4Multiply(GLKMatrix4Multiply(GLKMatrix4Multiply(earthTranslation, moonTranslation), rotation), scale);
    }
    
    [self.glkView display];
    self.sunDegree += 0.05f;
    self.earthDegree += 0.50f;
    self.earthRevolution += 0.10f;
    self.moonDegree += 1.50f;
    self.moonRevolution += 2.00f;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    // 顶点数
    int vert_count = sizeof(sphereVerts) / (sizeof(float) * 3);
    
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 启用深度测试，必须先设置drawableDepthFormat
    glEnable(GL_DEPTH_TEST);
    // 当深度值小于等于的时候绘制，默认是GL_LESS
    glDepthFunc(GL_LEQUAL);
    // 启用着色器
    [self.program use];
    // model、view、projection
    glUniformMatrix4fv([self.program uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&_viewMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&_projectionMatrix);
    
    // 开启blend混合模式
    glEnable(GL_BLEND);
    // 预乘alpha（premultiply）
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    // 没有预乘alpha（unpremultiply）
    // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
    // 绘制轨道
    glBindVertexArrayOES(_VAO);
    {
        glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&_orbitModelMatrix);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, self.orbitInfo.name);
        glUniform1i([self.program uniformIndex:@"inputImageTexture"], 2);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    glBindVertexArrayOES(0);
    // 关闭blend混合模式
    glDisable(GL_BLEND);
    
    // !!! 注意，轨道图片我们需要丢弃透明部分，shader里使用discard关键字
    // !!! 丢弃透明部分的原因是，片元被丢弃之后，不会写入深度值，这样之后绘制的球体不会被轨道遮挡
    
    // 绘制太阳、地球、月球
    glBindVertexArrayOES(_VAO1);
    {
        glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&_sunModelMatrix);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, self.sunInfo.name);
        glUniform1i([self.program uniformIndex:@"inputImageTexture"], 2);
        glDrawArrays(GL_TRIANGLES, 0, vert_count);
    }
    {
        glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&_earthModelMatrix);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, self.earthInfo.name);
        glUniform1i([self.program uniformIndex:@"inputImageTexture"], 2);
        glDrawArrays(GL_TRIANGLES, 0, vert_count);
    }
    {
        glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&_moonModelMatrix);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, self.moonInfo.name);
        glUniform1i([self.program uniformIndex:@"inputImageTexture"], 2);
        glDrawArrays(GL_TRIANGLES, 0, vert_count);
    }
    glBindVertexArrayOES(0);
    glDisable(GL_DEPTH_TEST);
}

- (void)dealloc
{
    if (_VAO) {
        glDeleteVertexArraysOES(1, &_VAO);
        _VAO = 0;
    }
    if (_VBO0) {
        glDeleteBuffers(1, &_VBO0);
        _VBO0 = 0;
    }
    if (_VBO1) {
        glDeleteBuffers(1, &_VBO1);
        _VBO1 = 0;
    }
    
    if (_VAO1) {
        glDeleteVertexArraysOES(1, &_VAO1);
        _VAO1 = 0;
    }
    if (_VBO10) {
        glDeleteBuffers(1, &_VBO10);
        _VBO10 = 0;
    }
    if (_VBO11) {
        glDeleteBuffers(1, &_VBO11);
        _VBO11 = 0;
    }
}

@end
