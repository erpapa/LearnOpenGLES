//
//  DemoViewController10.m
//  LearnOpenGLES
//
//  Created by apple on 2019/7/29.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController10.h"
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

@interface DemoViewController10 () <GLKViewDelegate>
{
    GLint _filterPositionAttribute;
    GLint _filterSourceColorAttribute;
    GLKMatrix4 _modelMatrix, _viewMatrix, _projectionMatrix;
    GLKVector3 _cameraPos;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLProgram *program;

@end

@implementation DemoViewController10

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
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_10" fragmentShaderFilename:@"shaderf_10"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"sourceColor"];
    [self.program link];
    
    _filterPositionAttribute = [self.program attributeIndex:@"position"];
    _filterSourceColorAttribute = [self.program attributeIndex:@"sourceColor"];
    [self.program use]; // 加载并使用链接好的程序
    
    // 摄像机位置
    _cameraPos = GLKVector3Make(0.0, 0.0, 1.0);
    // 初始化模型矩阵
    _modelMatrix = GLKMatrix4Identity;
    // 设置摄像机在(0，0，1)坐标，看向(0，0，0)点。Y轴正向为摄像机顶部指向的方向
    _viewMatrix = GLKMatrix4MakeLookAt(_cameraPos.x, _cameraPos.y, _cameraPos.z, 0, 0, 0, 0, 1, 0);
    // 正交投影矩阵
    _projectionMatrix = GLKMatrix4MakeOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
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
    
    // 启用着色器
    [self.program use];
    
    // 思考：为什么要设置视图矩阵，不设置视图矩阵会得出什么结果？
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
    
    glDisableVertexAttribArray(_filterPositionAttribute);
    glDisableVertexAttribArray(_filterSourceColorAttribute);
    
    glDisable(GL_DEPTH_TEST);
    
    // 回答上面的思考题，如果不设置视图矩阵，直接绘制方块，那么红色方块还是会被绿色方块盖住！！！
    // 解释：顶点的坐标本身就处于 [-1, 1] 范围内，我们也未做任何坐标变换，因此这些坐标就等于最终的 NDC 坐标值。
    // NDC 是基于左手坐标系，则 z 轴上的坐标值越小，就越显示在前面（左手坐标系 z 轴正方向指向屏幕内，与右手坐标系刚好相反）。
    // 而本例中绿色方块 z 值比红色方块 z 值小，所以优先显示绿色方块，红色方块被遮挡。
    // https://my.oschina.net/iirecord/blog/824029
}

@end
