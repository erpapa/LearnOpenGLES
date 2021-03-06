//
//  DemoViewController9.m
//  LearnOpenGLES
//
//  Created by apple on 2018/11/6.
//  Copyright © 2018 erpapa. All rights reserved.
//

#import "DemoViewController9.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import "GPUImagePicture.h"
#import "GLProgram.h"

static float skyboxVertices[] = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

@interface DemoViewController9 () <GLKViewDelegate>
{
    GLuint _VAO, _VBO;
    GLint _positionAttribute, _skyboxTextureUniform;
    GLKMatrix4 _modelMatrix, _viewMatrix, _projectionMatrix;
    GLuint _cubeTexture;
}

@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLProgram *program;

//@property (nonatomic, assign) GLKMatrix4 rotationMatrix;
@property (nonatomic, assign) GLKQuaternion endQuaternion;
@property (nonatomic, assign) GLKVector3 cameraEye;
@property (nonatomic, assign) GLKVector3 cameraForward;
@property (nonatomic, assign) GLKVector3 cameraUp;

@end

@implementation DemoViewController9

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
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_9" fragmentShaderFilename:@"shaderf_9"];
    [self.program addAttribute:@"position"];
    [self.program link];
    
    // 顶点
    _positionAttribute = [self.program attributeIndex:@"position"];
    _skyboxTextureUniform = [self.program uniformIndex:@"skyboxTexture"];
    
    // 创建索引缓冲对象
    glGenVertexArraysOES(1, &_VAO);
    glGenBuffers(1, &_VBO);
    
    // 绑定VAO
    glBindVertexArrayOES(_VAO);
    
    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    // 位置属性
    glEnableVertexAttribArray(_positionAttribute);
    glVertexAttribPointer(_positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    
    // glBindBuffer(GL_ARRAY_BUFFER, 0); // 不可以解绑，此时VAO管理着它们
    glBindVertexArrayOES(0); // 解绑VAO（这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法）
    
    // 加载纹理
    NSArray *images = [NSArray arrayWithObjects:@"skybox_right.jpg", @"skybox_left.jpg", @"skybox_top.jpg", @"skybox_bottom.jpg", @"skybox_front.jpg", @"skybox_back.jpg", nil];
    glGenTextures(1, &_cubeTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeTexture);
    for (unsigned int index = 0; index < images.count; index++) {
        NSString *imageName = [images objectAtIndex:index];
        GPUImagePicture *picture = [[GPUImagePicture alloc] initWithImage:[UIImage imageNamed:imageName] smoothlyScaleOutput:NO removePremultiplication:NO flipped:NO];
        CGSize imageSize = picture.pixelSizeOfImage;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGBA, imageSize.width, imageSize.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, picture.data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    self.cameraEye = GLKVector3Make(0, 0, 0);
    // 默认l看向(0，0，1)，需要Y轴旋转180°，看向(0，0，-1)
    // self.rotationMatrix = GLKMatrix4MakeRotation(M_PI, 0, 1, 0);
    self.endQuaternion = GLKQuaternionMakeWithAngleAndAxis(M_PI, 0, 1, 0);
    self.cameraForward = GLKMatrix4MultiplyVector3(GLKMatrix4MakeWithQuaternion(self.endQuaternion), GLKVector3Make(0, 0, 1));
    self.cameraUp = GLKVector3Make(0, 1, 0);
    // 初始化模型矩阵
    _modelMatrix = GLKMatrix4Identity;
    // 设置摄像机在(0, 0, 0)坐标，看向(0，0，-1)点。Y轴正向为摄像机顶部指向的方向
    _viewMatrix = GLKMatrix4MakeLookAt(self.cameraEye.x, self.cameraEye.y, self.cameraEye.z, self.cameraForward.x, self.cameraForward.y, self.cameraForward.z, self.cameraUp.x, self.cameraUp.y, self.cameraUp.z);
    // 使用透视投影矩阵，视场角设置为60°
    _projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(60.0), 1.0f, 0.1f, 100.0f);
    // 正交投影矩阵
    // projectionMatrix = GLKMatrix4MakeOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    [self.glkView display];
}

#pragma mark - 处理触摸事件

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self.glkView display];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    // 计算滑动
    CGPoint currentPoint = [[touches anyObject] locationInView:self.view];
    CGPoint previousPoint = [[touches anyObject] previousLocationInView:self.view];
    CGFloat rotx = GLKMathDegreesToRadians((currentPoint.y - previousPoint.y) * -0.1);
    CGFloat roty = GLKMathDegreesToRadians((currentPoint.x - previousPoint.x) * 0.1);
    
    // 注意：会有万向节锁的问题，解决办法是使用四元数
//    GLKMatrix4 rotation = GLKMatrix4Multiply(GLKMatrix4MakeRotation(roty, 0, 1, 0), GLKMatrix4MakeRotation(rotx, 1, 0, 0));
//    self.rotationMatrix = GLKMatrix4Multiply(self.rotationMatrix, rotation);
    GLKQuaternion quaternion = GLKQuaternionMultiply(GLKQuaternionMakeWithAngleAndAxis(roty, 0, 1, 0), GLKQuaternionMakeWithAngleAndAxis(rotx, 1, 0, 0));
    self.endQuaternion = GLKQuaternionMultiply(self.endQuaternion, quaternion);
    self.cameraForward = GLKMatrix4MultiplyVector3(GLKMatrix4MakeWithQuaternion(self.endQuaternion), GLKVector3Make(0, 0, 1));
    // 摄像机坐标不变，改变的看向的点
    _viewMatrix = GLKMatrix4MakeLookAt(self.cameraEye.x, self.cameraEye.y, self.cameraEye.z, self.cameraForward.x, self.cameraForward.y, self.cameraForward.z, self.cameraUp.x, self.cameraUp.y, self.cameraUp.z);
    
    [self.glkView display];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self.glkView display];
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self.glkView display];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 启用深度测试，必须先设置drawableDepthFormat
    glEnable(GL_DEPTH_TEST);

    // glDepthMask(GLboolean)深度缓冲区是否可写，默认可写
    // 注意，在绘制半透明物体时前，将深度缓冲区设置为只读形式
    glDepthMask(GL_FALSE);
    // 遮挡优化，当深度值小于等于的时候绘制，默认是GL_LESS
    glDepthFunc(GL_LEQUAL);
    // 启用着色器
    [self.program use];
    
    // model、view、projection
    glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&_modelMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&_viewMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&_projectionMatrix);
    
    // cube
    glBindVertexArrayOES(_VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeTexture);
    glUniform1i(_skyboxTextureUniform, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArrayOES(0);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    
    glDisable(GL_DEPTH_TEST);
}

- (void)dealloc
{
    if (_VAO) {
        glDeleteVertexArraysOES(1, &_VAO);
        _VAO = 0;
    }
    if (_VBO) {
        glDeleteBuffers(1, &_VBO);
        _VBO = 0;
    }
    if (_cubeTexture) {
        glDeleteTextures(1, &_cubeTexture);
        _cubeTexture = 0;
    }
}

@end
