//
//  DemoViewController8.m
//  LearnOpenGLES
//
//  Created by apple on 2018/11/1.
//  Copyright © 2018 erpapa. All rights reserved.
//

#import "DemoViewController8.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import "GLProgram.h"
#include "sphere.h"

@interface DemoViewController8 () <GLKViewDelegate>
{
    GLuint VAO, VBO0, VBO1;
    GLint positionAttribute, textureCoordinateAttribute;
    GLKMatrix4 sunModelMatrix, earthModelMatrix, moonModelMatrix, viewMatrix, projectionMatrix;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *sunInfo;
@property (nonatomic, strong) GLKTextureInfo *earthInfo;
@property (nonatomic, strong) GLKTextureInfo *moonInfo;
@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) GLProgram *program;

@property (nonatomic, assign) float sunDegree; // 太阳自转
@property (nonatomic, assign) float earthDegree; // 地球自转
@property (nonatomic, assign) float earthRevolution; // 地球公转
@property (nonatomic, assign) float moonDegree; // 月球自转
@property (nonatomic, assign) float moonRevolution; // 月球公转

@end

@implementation DemoViewController8

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
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_8" fragmentShaderFilename:@"shaderf_8"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"inputTextureCoordinate"];
    [self.program link];
    
    // 顶点
    positionAttribute = [self.program attributeIndex:@"position"];
    textureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    
    // 创建索引缓冲对象
    glGenVertexArraysOES(1, &VAO);
    glGenBuffers(1, &VBO0);
    glGenBuffers(1, &VBO1);
    
    // 绑定VAO
    glBindVertexArrayOES(VAO);
    
    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphereVerts), sphereVerts, GL_STATIC_DRAW);
    
    // 位置属性
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttribute);
    
    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphereTexCoords), sphereTexCoords, GL_STATIC_DRAW);
    // 纹理
    glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(textureCoordinateAttribute);
    
    // glBindBuffer(GL_ARRAY_BUFFER, 0); // 这个方法将顶点属性指针注册到VBO作为当前绑定顶点对象，然后我们就可以安全的解绑
    glBindVertexArrayOES(0); // 解绑 VAO (这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法)
    glEnable(GL_DEPTH_TEST); // 启用深度测试，必须先设置drawableDepthFormat
    
    // texture
    NSString *sunFilePath = [[NSBundle mainBundle] pathForResource:@"sun" ofType:@"jpg"];
    self.sunInfo = [GLKTextureLoader textureWithContentsOfFile:sunFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    NSString *earthFilePath = [[NSBundle mainBundle] pathForResource:@"earth_diffuse" ofType:@"jpg"];
    self.earthInfo = [GLKTextureLoader textureWithContentsOfFile:earthFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    NSString *moonFilePath = [[NSBundle mainBundle] pathForResource:@"moon" ofType:@"jpg"];
    self.moonInfo = [GLKTextureLoader textureWithContentsOfFile:moonFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    
    // 初始化模型矩阵
    sunModelMatrix = GLKMatrix4Identity;
    earthModelMatrix = GLKMatrix4Identity;
    moonModelMatrix = GLKMatrix4Identity;
    // 设置摄像机在(0，3.0，10.0)坐标，看向(0，0，0)点。Y轴正向为摄像机顶部指向的方向
    viewMatrix = GLKMatrix4MakeLookAt(0.0, 3.0, 10.0, 0, 0, 0, 0, 1, 0);
    // 使用透视投影矩阵，视场角设置为90°
    projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90.0f), 1.0f, 0.1f, 100.0f);
    // 正交投影矩阵
    // projectionMatrix = GLKMatrix4MakeOrtho(-10.0, 10.0, -10.0, 10.0, 10.0, 100.0);
    
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
        sunModelMatrix = GLKMatrix4Multiply(rotation, scale);
    }
    // 地球
    {
        // 缩放
        GLKMatrix4 scale = GLKMatrix4MakeScale(1.2, 1.2, 1.2);
        // 地球自转
        float radians = GLKMathDegreesToRadians(self.earthDegree);
        GLKMatrix4 rotation = GLKMatrix4MakeRotation(radians, 0.0, 1.0, 0.0);
        // 地球公转
        float revolution = GLKMathDegreesToRadians(self.earthRevolution);
        float cos = cosf(revolution);
        float sin = sinf(revolution);
        GLKMatrix4 translation = GLKMatrix4MakeTranslation(6.0 * sin, 0.0, 6.0 * cos);
        earthModelMatrix = GLKMatrix4Multiply(GLKMatrix4Multiply(translation, rotation), scale);
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
        moonModelMatrix = GLKMatrix4Multiply(GLKMatrix4Multiply(GLKMatrix4Multiply(earthTranslation, moonTranslation), rotation), scale);
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
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    [self.program use];
    
    // model、view、projection
    glUniformMatrix4fv([self.program uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&viewMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&projectionMatrix);
    
    // 绘制太阳、地球、月球
    glBindVertexArrayOES(VAO);

    int vert_count = sizeof(sphereVerts) / (sizeof(float) * 3);
    glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&sunModelMatrix);
    glActiveTexture([self.program uniformIndex:@"inputImageTexture"]);
    glBindTexture(GL_TEXTURE_2D, self.sunInfo.name);
    glDrawArrays(GL_TRIANGLES, 0, vert_count);

    glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&earthModelMatrix);
    glActiveTexture([self.program uniformIndex:@"inputImageTexture"]);
    glBindTexture(GL_TEXTURE_2D, self.earthInfo.name);
    glDrawArrays(GL_TRIANGLES, 0, vert_count);

    glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&moonModelMatrix);
    glActiveTexture([self.program uniformIndex:@"inputImageTexture"]);
    glBindTexture(GL_TEXTURE_2D, self.moonInfo.name);
    glDrawArrays(GL_TRIANGLES, 0, vert_count);

    glBindVertexArrayOES(0);
}

- (void)dealloc
{
    [self.program validate];
    self.program = nil;
    
    if (VAO) {
        glDeleteVertexArraysOES(1, &VAO);
        VAO = 0;
    }
    if (VBO0) {
        glDeleteBuffers(1, &VBO0);
        VBO0 = 0;
    }
    if (VBO1) {
        glDeleteBuffers(1, &VBO1);
        VBO1 = 0;
    }
}

@end
