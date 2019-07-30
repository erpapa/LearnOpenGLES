//
//  DemoViewController1.m
//  LearnOpenGLES
//
//  Created by erpapa on 2018/2/7.
//  Copyright © 2018年 erpapa. All rights reserved.
//

#import "DemoViewController1.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"

typedef struct {
    GLfloat positon[3];//位置
    GLfloat color[4];//颜色
    GLfloat texCoord[2];//纹理
} Vertex;

static Vertex vertexData[] = {
    -1.0f, -1.0f, 0.0,     1.0, 0.0, 0.0, 1.0,   1.0f, 0.0f, // 0 左下
    1.0f, -1.0f, 0.0,     1.0, 1.0, 0.0, 1.0,   0.0f, 1.0f, // 1 右下
    -1.0f, 1.0f, 0.0,    0.0, 0.0, 1.0, 1.0,   0.0f, 0.0f, // 2 左上
    1.0f, 1.0f, 0.0,    1.0, 1.0, 1.0, 1.0,   0.0f, 1.0f // 3 右上
};

@interface DemoViewController1 () <GLKViewDelegate>
{
    GLint filterPositionAttribute;
    GLint filterSourceColorAttribute;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLProgram *program;

@end

@implementation DemoViewController1

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    // shader
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_1" fragmentShaderFilename:@"shaderf_1"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"sourceColor"];
    [self.program link];
    
    filterPositionAttribute = [self.program attributeIndex:@"position"];
    filterSourceColorAttribute = [self.program attributeIndex:@"sourceColor"];
    [self.program use]; // 加载并使用链接好的程序
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    [self.program use];
    glEnableVertexAttribArray(filterPositionAttribute); // 启用属性
    glEnableVertexAttribArray(filterSourceColorAttribute); // 启用属性
    // 参数含义分别为：顶点属性索引（这里是位置）、3个分量的矢量、类型是浮点（GL_FLOAT）、填充时不需要单位化（GL_FALSE）； sizeof(Vertex)==4*8==32（GL_FLOAT占4个字节，每行有8个浮点数），如果数据连续存放，则为0；最后一个参数是一个偏移量的指针，用来确定“第一个数据”将从内存数据块的什么地方开始。
    glVertexAttribPointer(filterPositionAttribute, 3, GL_FLOAT, 0, sizeof(Vertex), (float *)vertexData + 0);
    glVertexAttribPointer(filterSourceColorAttribute, 4, GL_FLOAT, 0, sizeof(Vertex), (float *)vertexData + 3);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(filterPositionAttribute);
    glDisableVertexAttribArray(filterSourceColorAttribute);
}

- (void)dealloc
{
    [self.program validate];
    self.program = nil;
}

@end

