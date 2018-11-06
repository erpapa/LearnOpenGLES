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

@interface DemoViewController9 () <GLKViewDelegate>
{
    GLuint VAO, VBO;
    GLint positionAttribute, skyboxTextureUniform;
    GLKMatrix4 modelMatrix, viewMatrix, projectionMatrix;
}

@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLProgram *program;
@property (nonatomic, assign) GLuint cubeTexture;

@property (nonatomic, assign) float xDegree;
@property (nonatomic, assign) float yDegree;

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
    positionAttribute = [self.program attributeIndex:@"position"];
    skyboxTextureUniform = [self.program uniformIndex:@"skyboxTexture"];
    
    // 顶点数组
    float skyboxVertices[] = {
        // positions
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
    
    // 创建索引缓冲对象
    glGenVertexArraysOES(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // 绑定VAO
    glBindVertexArrayOES(VAO);
    
    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    // 位置属性
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttribute);
    
    // glBindBuffer(GL_ARRAY_BUFFER, 0); // 这个方法将顶点属性指针注册到VBO作为当前绑定顶点对象，然后我们就可以安全的解绑
    glBindVertexArrayOES(0); // 解绑 VAO (这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法)
    glEnable(GL_DEPTH_TEST); // 启用深度测试，必须先设置drawableDepthFormat
    
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

    // 初始化模型矩阵
    modelMatrix = GLKMatrix4Identity;
    // 设置摄像机在(0, 0, 0)坐标，看向(0，0，-0.5)点。Y轴正向为摄像机顶部指向的方向
    viewMatrix = GLKMatrix4MakeLookAt(0.0, 0.0, 0.0, 0, 0, -0.5, 0, 1, 0);
    // 使用透视投影矩阵，视场角设置为90°
    projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90.0f), 1.0f, 0.1f, 100.0f);
    // 正交投影矩阵
    // projectionMatrix = GLKMatrix4MakeOrtho(-10.0, 10.0, -10.0, 10.0, 10.0, 100.0);
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
    // 左右滑动改变X轴
    self.xDegree += (currentPoint.x - previousPoint.x) * 0.5;
    CGFloat x = -0.5 * sin(GLKMathDegreesToRadians(self.xDegree));
    // 上下滑动改变Y轴
    self.yDegree += (currentPoint.y - previousPoint.y) * 0.5;
    CGFloat y = 0.5 * sin(GLKMathDegreesToRadians(self.yDegree));
    // 摄像机坐标不变，改变的看向的点
    viewMatrix = GLKMatrix4MakeLookAt(0.0, 0.0, 0.0, x, y, -0.5, 0, 1, 0);
    
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
    
    // glDepthMask(GLboolean)深度缓冲区是否可写，默认可写
    // 注意，在绘制半透明物体时前，将深度缓冲区设置为只读形式
    glDepthMask(GL_FALSE);
    // 遮挡优化
    glDepthFunc(GL_LEQUAL);
    [self.program use];
    
    // model、view、projection
    glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&modelMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&viewMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&projectionMatrix);
    
    // cube
    glBindVertexArrayOES(VAO);
    glActiveTexture(skyboxTextureUniform);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArrayOES(0);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}

- (void)dealloc
{
    [self.program validate];
    self.program = nil;
    
    if (VAO) {
        glDeleteVertexArraysOES(1, &VAO);
        VAO = 0;
    }
    if (VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (_cubeTexture) {
        glDeleteTextures(1, &_cubeTexture);
        _cubeTexture = 0;
    }
}

@end
