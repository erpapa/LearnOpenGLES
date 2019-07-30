//
//  DemoViewController7.m
//  LearnOpenGLES
//
//  Created by apple on 2018/10/25.
//  Copyright © 2018 erpapa. All rights reserved.
//

#import "DemoViewController7.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import "GLProgram.h"

@interface DemoViewController7 () <GLKViewDelegate>
{
    GLuint VAO, VBO;
    GLint positionAttribute, textureCoordinateAttribute;
    GLKMatrix4 modelMatrix, viewMatrix, projectionMatrix;
    GLKVector3 cameraPos;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) GLProgram *program;
@property (nonatomic, assign) float degree; // 旋转

@end

@implementation DemoViewController7

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
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_7" fragmentShaderFilename:@"shaderf_7"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"inputTextureCoordinate"];
    [self.program link];
    
    // 顶点
    positionAttribute = [self.program attributeIndex:@"position"];
    textureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    
    // 不使用索引缓冲对象用两个三角形绘制一个梯形
    // 设置顶点缓存和属性指针
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // 创建索引缓冲对象
    glGenVertexArraysOES(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // 绑定VAO
    glBindVertexArrayOES(VAO);

    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 位置属性
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttribute);
    // 纹理
    glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(textureCoordinateAttribute);
    
    // glBindBuffer(GL_ARRAY_BUFFER, 0); // 不可以解绑，此时VAO管理着它们
    glBindVertexArrayOES(0); // 解绑VAO（这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法）
    glEnable(GL_DEPTH_TEST); // 启用深度测试，必须先设置drawableDepthFormat

    // texture
    NSString *diffuseFilePath = [[NSBundle mainBundle] pathForResource:@"container_diffuse" ofType:@"jpg"];
    self.textureInfo = [GLKTextureLoader textureWithContentsOfFile:diffuseFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    
    // 摄像机位置
    cameraPos = GLKVector3Make(1.0, 1.0, 1.0);
    // 初始化模型矩阵
    modelMatrix = GLKMatrix4Identity;
    // 设置摄像机在(1，1，1)坐标，看向(0，0，0)点。Y轴正向为摄像机顶部指向的方向
    viewMatrix = GLKMatrix4MakeLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);
    // 使用透视投影矩阵，视场角设置为90°
    projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90.0f), 1.0f, 0.1f, 100.0f);
    
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
    float radians = GLKMathDegreesToRadians(self.degree);
    // 模型绕Y轴旋转
    // modelMatrix = GLKMatrix4MakeRotation(radians, 0.0, 1.0, 0.0);
    // 摄像机绕模型Y旋转（改变摄像机位置，模型不动）
    cameraPos = GLKMatrix4MultiplyVector3(GLKMatrix4MakeRotation(radians, 0.0, 1.0, 0.0), GLKVector3Make(1.0, 1.0, 1.0));
    viewMatrix = GLKMatrix4MakeLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);
    [self.glkView display];
    self.degree += 0.5f;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    [self.program use];
    // model、view、projection
    glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&modelMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&viewMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&projectionMatrix);
    
    // bind texture
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, self.textureInfo.name);
    glUniform1i([self.program uniformIndex:@"inputImageTexture"], 2);
    
    glBindVertexArrayOES(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
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
    if (VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
}

@end
