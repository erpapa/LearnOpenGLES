//
//  DemoViewController19.m
//  LearnOpenGLES
//
//  Created by apple on 2019/8/25.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController19.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import "GLProgram.h"

// 位置和法线
static GLfloat boxVertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

@interface DemoViewController19 () <GLKViewDelegate>
{
    GLuint _lightVAO, _lightVBO, _modelVAO, _modelVBO;
    GLint _lightPositionAttribute, _lightNormalAttribute, _modelPositionAttribute, _modelNormalAttribute;
    GLKMatrix4 _lightMatrix, _modelMatrix, _viewMatrix, _projectionMatrix;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLProgram *lightProgram;
@property (nonatomic, strong) GLProgram *modelProgram;

@end

@implementation DemoViewController19

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    // shader
    self.lightProgram = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_18" fragmentShaderFilename:@"shaderf_18"];
    [self.lightProgram addAttribute:@"position"];
    [self.lightProgram addAttribute:@"normal"];
    [self.lightProgram link];
    _lightPositionAttribute = [self.lightProgram attributeIndex:@"position"];
    _lightNormalAttribute = [self.lightProgram attributeIndex:@"normal"];
    
    self.modelProgram = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_19" fragmentShaderFilename:@"shaderf_19"];
    [self.modelProgram addAttribute:@"position"];
    [self.modelProgram addAttribute:@"normal"];
    [self.modelProgram link];
    _modelPositionAttribute = [self.modelProgram attributeIndex:@"position"];
    _modelNormalAttribute = [self.modelProgram attributeIndex:@"normal"];
    
    // 1.创建灯光
    {
        glGenVertexArraysOES(1, &_lightVAO);
        glGenBuffers(1, &_lightVBO);
        
        glBindVertexArrayOES(_lightVAO);
        glBindBuffer(GL_ARRAY_BUFFER, _lightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(_lightPositionAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(_lightPositionAttribute);
        glVertexAttribPointer(_lightNormalAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(_lightNormalAttribute);
        
        // glBindBuffer(GL_ARRAY_BUFFER, 0); // 不可以解绑，此时VAO管理着它们
        glBindVertexArrayOES(0); // 解绑VAO（这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法）
    }
    // 2.创建物体
    {
        glGenVertexArraysOES(1, &_modelVAO);
        glGenBuffers(1, &_modelVBO);
        
        glBindVertexArrayOES(_modelVAO);
        glBindBuffer(GL_ARRAY_BUFFER, _modelVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(_modelPositionAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(_modelPositionAttribute);
        glVertexAttribPointer(_modelNormalAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(_modelNormalAttribute);
        
        // glBindBuffer(GL_ARRAY_BUFFER, 0); // 不可以解绑，此时VAO管理着它们
        glBindVertexArrayOES(0); // 解绑VAO（这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法）
    }
    
    // 初始化模型矩阵
    _lightMatrix = GLKMatrix4Multiply(GLKMatrix4MakeTranslation(-0.5, 1.0, -1.0), GLKMatrix4MakeScale(0.25, 0.25, 0.25));
    _modelMatrix = GLKMatrix4Identity;
    // 设置摄像机在(1，1，1)坐标，看向(0，0，0)点。Y轴正向为摄像机顶部指向的方向
    _viewMatrix = GLKMatrix4MakeLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // 使用透视投影矩阵，视场角设置为90°
    _projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90.0f), 1.0f, 0.1f, 100.0f);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 启用深度测试，必须先设置drawableDepthFormat
    glEnable(GL_DEPTH_TEST);
    // 当深度值小于等于的时候绘制，默认是GL_LESS
    glDepthFunc(GL_LEQUAL);
    
    // 1.绘制灯光
    {
        [self.lightProgram use];
        // model、view、projection
        glUniformMatrix4fv([self.lightProgram uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&_lightMatrix);
        glUniformMatrix4fv([self.lightProgram uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&_viewMatrix);
        glUniformMatrix4fv([self.lightProgram uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&_projectionMatrix);
        
        // objectColor、ambientColor
        glUniform3f([self.lightProgram uniformIndex:@"objectColor"], 1.0, 1.0, 1.0);
        glUniform3f([self.lightProgram uniformIndex:@"ambientColor"], 1.0, 1.0, 1.0);
        
        glBindVertexArrayOES(_lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArrayOES(0);
    }
    // 2.绘制物体
    {
        [self.modelProgram use];
        // model、view、projection
        glUniformMatrix4fv([self.modelProgram uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&_modelMatrix);
        glUniformMatrix4fv([self.modelProgram uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&_viewMatrix);
        glUniformMatrix4fv([self.modelProgram uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&_projectionMatrix);
        
        // objectColor、ambientColor、lightColor
        glUniform3f([self.modelProgram uniformIndex:@"objectColor"], 1.0f, 0.5f, 0.31f);
        glUniform3f([self.modelProgram uniformIndex:@"ambientColor"], 0.2f, 0.2f, 0.2f);
        glUniform3f([self.modelProgram uniformIndex:@"lightColor"], 1.0, 1.0, 1.0);
        glUniform3f([self.modelProgram uniformIndex:@"lightPosition"], -0.5, 1.0, -1.0);
        
        glBindVertexArrayOES(_modelVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArrayOES(0);
    }
    
    glDisable(GL_DEPTH_TEST);
}

- (void)dealloc
{
    if (_lightVAO) {
        glDeleteVertexArraysOES(1, &_lightVAO);
        _lightVAO = 0;
    }
    if (_lightVBO) {
        glDeleteBuffers(1, &_lightVBO);
        _lightVBO = 0;
    }
    if (_modelVAO) {
        glDeleteVertexArraysOES(1, &_modelVAO);
        _modelVAO = 0;
    }
    if (_modelVBO) {
        glDeleteBuffers(1, &_modelVBO);
        _modelVBO = 0;
    }
}

@end
