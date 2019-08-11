//
//  DemoViewController15.m
//  LearnOpenGLES
//
//  Created by apple on 2019/7/29.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController15.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"

typedef struct {
    GLfloat positon[3];//位置
    GLfloat color[4];//颜色
    GLfloat texCoord[2];//纹理
} Vertex;

static Vertex ccwVertexData[] = { // 逆时针（0->1->2 2->1->3）
    -0.75f, -0.75f, 0.0,     1.0, 0.0, 0.0, 1.0,   1.0f, 0.0f, // 0 左下
    0.25f, -0.75f, 0.0,     1.0, 0.0, 0.0, 1.0,   0.0f, 1.0f, // 1 右下
    -0.75f, 0.25f, 0.0,    1.0, 0.0, 0.0, 1.0,   0.0f, 0.0f, // 2 左上
    0.25f, 0.25f, 0.0,    1.0, 0.0, 0.0, 1.0,   0.0f, 1.0f // 3 右上
};

static Vertex cwVertexData[] = { // 顺时针（0->1->2 2->1->3）
    -0.25f, 0.75f, -0.5,     0.0, 1.0, 0.0, 1.0,   0.0f, 0.0f, // 0 左上
    0.75f, 0.75f, -0.5,     0.0, 1.0, 0.0, 1.0,   0.0f, 1.0f // 1 右上
    -0.25f, -0.25f, -0.5,   0.0, 1.0, 0.0, 1.0,   1.0f, 0.0f, // 2 左下
    0.75f, -0.25f, -0.5,   0.0, 1.0, 0.0, 1.0,   0.0f, 1.0f, // 3 右下
};

@interface DemoViewController15 () <GLKViewDelegate>
{
    GLint filterPositionAttribute;
    GLint filterSourceColorAttribute;
    GLKMatrix4 modelMatrix, viewMatrix, projectionMatrix;
    GLKVector3 cameraPos;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLProgram *program;

@end

@implementation DemoViewController15

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
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_15" fragmentShaderFilename:@"shaderf_15"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"sourceColor"];
    [self.program link];
    
    filterPositionAttribute = [self.program attributeIndex:@"position"];
    filterSourceColorAttribute = [self.program attributeIndex:@"sourceColor"];
    [self.program use]; // 加载并使用链接好的程序
    
    // 摄像机位置
    cameraPos = GLKVector3Make(0.0, 0.0, 1.0);
    // 初始化模型矩阵
    modelMatrix = GLKMatrix4Identity;
    // 设置摄像机在(0，0，1)坐标，看向(0，0，0)点。Y轴正向为摄像机顶部指向的方向
    viewMatrix = GLKMatrix4MakeLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);
    // 正交投影矩阵
    projectionMatrix = GLKMatrix4MakeOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    /**
     * 指定清除颜色缓冲后赋值的默认颜色
     **/
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    /**
     * 1.如果指定“当前像素值”为1时，我们知道，一个模型深度值取值和范围为[0,1]。
     这个时候你往里面画一个物体，由于物体的每个像素的深度值都小于等于1， 所以整个物体都被显示了出来。
     * 2.如果指定“当前像素值”为0，物体的每个像素的深度值都大于等于0，所以整个物体都不可见。
     * 3.如果指定“当前像素值”为0.5，那么物体就只有深度小于等于0.5的那部分才是可见的。
     **/
    glClearDepthf(1.0f);
    // 清除颜色缓冲和深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 启用深度测试，必须先设置drawableDepthFormat
    glEnable(GL_DEPTH_TEST);
    // 当深度值小于等于的时候绘制
    // 在OpenGL中深度指的就是在坐标系中像素Z的值，距离观察者的距离，观察者可以在任何位置，OpenGL中会有专门一块缓存区来存放Z值
    glDepthFunc(GL_LEQUAL);
    
    // 启用面剔除
    glEnable(GL_CULL_FACE);
    // 指定逆时针顺序为正面，参数的可选的值有GL_CW和GL_CCW(默认值是GL_CCW)
    glFrontFace(GL_CCW);
    // 背面剔除，参数的可选的值有GL_FRONT和GL_BACK和GL_FRONT_AND_BACK
    glCullFace(GL_BACK);
    
    // 启用着色器
    [self.program use];
    
    // model、view、projection
    glUniformMatrix4fv([self.program uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&modelMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&viewMatrix);
    glUniformMatrix4fv([self.program uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&projectionMatrix);
    
    glEnableVertexAttribArray(filterPositionAttribute); // 启用属性
    glEnableVertexAttribArray(filterSourceColorAttribute); // 启用属性
    
    // 1.绘制红色方块（顶点的排列顺序是逆时针，不会被剔除）
    glVertexAttribPointer(filterPositionAttribute, 3, GL_FLOAT, 0, sizeof(Vertex), (float *)ccwVertexData + 0);
    glVertexAttribPointer(filterSourceColorAttribute, 4, GL_FLOAT, 0, sizeof(Vertex), (float *)ccwVertexData + 3);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    // 2.绘制绿色方块（顶点的排列顺序是顺时针，会被剔除）
    glVertexAttribPointer(filterPositionAttribute, 3, GL_FLOAT, 0, sizeof(Vertex), (float *)cwVertexData + 0);
    glVertexAttribPointer(filterSourceColorAttribute, 4, GL_FLOAT, 0, sizeof(Vertex), (float *)cwVertexData + 3);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableVertexAttribArray(filterPositionAttribute);
    glDisableVertexAttribArray(filterSourceColorAttribute);
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}

- (void)dealloc
{
    [self.program validate];
    self.program = nil;
}
@end
