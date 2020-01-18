//
//  DemoViewController11.m
//  LearnOpenGLES
//
//  Created by apple on 2019/7/29.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController11.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"

typedef struct {
    GLfloat positon[3];//位置
    GLfloat color[4];//颜色
    GLfloat texCoord[2];//纹理
} ScenceVertex;

static ScenceVertex redVertexData[] = {
    -0.75f, -0.75f, 0.0,     1.0, 0.0, 0.0, 1.0,   1.0f, 0.0f, // 0 左下
    0.25f, -0.75f, 0.0,     1.0, 0.0, 0.0, 1.0,   0.0f, 1.0f, // 1 右下
    -0.75f, 0.25f, 0.0,    1.0, 0.0, 0.0, 1.0,   0.0f, 0.0f, // 2 左上
    0.25f, 0.25f, 0.0,    1.0, 0.0, 0.0, 1.0,   0.0f, 1.0f // 3 右上
};

static ScenceVertex greenVertexData[] = {
    -0.25f, -0.25f, -0.5,     0.0, 1.0, 0.0, 1.0,   1.0f, 0.0f, // 0 左下
    0.75f, -0.25f, -0.5,     0.0, 1.0, 0.0, 1.0,   0.0f, 1.0f, // 1 右下
    -0.25f, 0.75f, -0.5,    0.0, 1.0, 0.0, 1.0,   0.0f, 0.0f, // 2 左上
    0.75f, 0.75f, -0.5,    0.0, 1.0, 0.0, 1.0,   0.0f, 1.0f // 3 右上
};

static ScenceVertex blueVertexData[] = {
    -1.0f, -1.0f, 0.5,     0.0, 0.0, 1.0, 1.0,   1.0f, 0.0f, // 0 左下
    1.0f, -1.0f, 0.5,     0.0, 0.0, 1.0, 1.0,   0.0f, 1.0f, // 1 右下
    -1.0f, 0.0f, 0.5,    0.0, 0.0, 1.0, 1.0,   0.0f, 0.0f, // 2 左上
    1.0f, 0.0f, 0.5,    0.0, 0.0, 1.0, 1.0,   0.0f, 1.0f // 3 右上
};

@interface DemoViewController11 () <GLKViewDelegate>
{
    GLint _filterPositionAttribute;
    GLint _filterSourceColorAttribute;
    GLKMatrix4 _modelMatrix, _viewMatrix, _projectionMatrix;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLProgram *program;

@end

@implementation DemoViewController11

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    self.glkView.drawableStencilFormat = GLKViewDrawableStencilFormat8;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    /*
    // FBO
    glGenFramebuffers(1, &_defaultFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _defaultFrameBuffer);
    
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, self.glkView.bounds.size.width, self.glkView.bounds.size.height);
    // 附加颜色缓冲
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
     
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, self.glkView.bounds.size.width, self.glkView.bounds.size.height);
    // 附加深度缓冲
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
    // 附加模板缓冲，可以与深度缓冲共用一个depthRenderBuffer，前提是internalformat设置为GL_DEPTH24_STENCIL8_OES
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    */
    
    // shader
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_10" fragmentShaderFilename:@"shaderf_10"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"sourceColor"];
    [self.program link];
    
    _filterPositionAttribute = [self.program attributeIndex:@"position"];
    _filterSourceColorAttribute = [self.program attributeIndex:@"sourceColor"];
    
    // 初始化模型矩阵
    _modelMatrix = GLKMatrix4Identity;
    // 设置摄像机在(0，0，1)坐标，看向(0，0，0)点。Y轴正向为摄像机顶部指向的方向
    _viewMatrix = GLKMatrix4MakeLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // 正交投影矩阵
    _projectionMatrix = GLKMatrix4MakeOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    [self.glkView display];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    /**
     * 指定清除颜色缓冲后赋值的默认颜色
     */
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    /**
     * 1.如果指定“当前像素值”为1时，我们知道，一个模型深度值取值和范围为[0,1]。
         这个时候你往里面画一个物体，由于物体的每个像素的深度值都小于等于1， 所以整个物体都被显示了出来。
     * 2.如果指定“当前像素值”为0，物体的每个像素的深度值都大于等于0，所以整个物体都不可见。
     * 3.如果指定“当前像素值”为0.5，那么物体就只有深度小于等于0.5的那部分才是可见的。
     */
    glClearDepthf(1.0f);
    // 指定清除模板缓冲区时使用的索引，初始值为0。
    glClearStencil(0);
    // 清除颜色缓冲、深度缓冲和模板缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // 启用深度测试，必须先设置drawableDepthFormat
    glEnable(GL_DEPTH_TEST);
    // 当深度值小于等于的时候绘制
    // 在OpenGL中深度指的就是在坐标系中像素Z的值，距离观察者的距离，观察者可以在任何位置，OpenGL中会有专门一块缓存区来存放Z值
    glDepthFunc(GL_LEQUAL);
    
    // 启用模板测试，必须先设置drawableStencilFormat
    glEnable(GL_STENCIL_TEST);
    /**
     * func：设置模板测试函数(Stencil Test Function)
     * ref：设置了模板测试的参考值(Reference Value)。模板缓冲的内容将会与这个值进行比较。
     * mask：设置一个掩码，它将会与参考值和储存的模板值在测试比较它们之前进行与(AND)运算。初始情况下所有位都为1。
     */
    glStencilFunc(GL_ALWAYS, 1, 1);
    /**
     * fail：模板测试失败。
     * zfail：模板测试通过，但深度测试失败。
     * zpass：模板测试通过，且深度测试通过。
     */
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    // 启用着色器
    [self.program use];
    
    // model、view、projection
    glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&_modelMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&_viewMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&_projectionMatrix);
    
    glEnableVertexAttribArray(_filterPositionAttribute); // 启用属性
    glEnableVertexAttribArray(_filterSourceColorAttribute); // 启用属性
    
    // 绘制【红色方块】和【绿色方块】，中间有0.5x0.5区域重叠
    // 虽然【绿色方块】在【红色方块】之后绘制，但是由于【绿色方块】的深度值大于【红色方块】，导致【绿色方块】有部分被遮挡
    
    // 1.绘制红色方块
    glVertexAttribPointer(_filterPositionAttribute, 3, GL_FLOAT, 0, sizeof(ScenceVertex), (float *)redVertexData + 0);
    glVertexAttribPointer(_filterSourceColorAttribute, 4, GL_FLOAT, 0, sizeof(ScenceVertex), (float *)redVertexData + 3);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    // 2.绘制绿色方块
    glVertexAttribPointer(_filterPositionAttribute, 3, GL_FLOAT, 0, sizeof(ScenceVertex), (float *)greenVertexData + 0);
    glVertexAttribPointer(_filterSourceColorAttribute, 4, GL_FLOAT, 0, sizeof(ScenceVertex), (float *)greenVertexData + 3);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    // 2.绘制蓝色方块
    // 整个屏幕的蒙板值已经发生了变化，需要再设置画绿色方块的蒙板参数
    glStencilFunc(GL_LEQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    
    glVertexAttribPointer(_filterPositionAttribute, 3, GL_FLOAT, 0, sizeof(ScenceVertex), (float *)blueVertexData + 0);
    glVertexAttribPointer(_filterSourceColorAttribute, 4, GL_FLOAT, 0, sizeof(ScenceVertex), (float *)blueVertexData + 3);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableVertexAttribArray(_filterPositionAttribute);
    glDisableVertexAttribArray(_filterSourceColorAttribute);
    
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    
    // 总结一下，最开始全屏的蒙板值是0，然后我们采用总是通过的方式画了红色正方形和绿色正方形，并设置蒙板值为1，
    // 这之后，红色正方形和绿色正方形的部分蒙板值为1，剩下地方仍然为0。接着以小于等于的形式来画蓝色正方形，比较值为1，
    // 这样，只有蓝色正方形和红色绿色正方形相交的地方，蓝色正方形才能画上去。
}

@end
