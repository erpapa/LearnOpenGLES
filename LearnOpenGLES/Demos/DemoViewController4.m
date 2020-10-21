//
//  DemoViewController4.m
//  LearnOpenGLES
//
//  Created by erpapa on 2018/2/7.
//  Copyright © 2018年 erpapa. All rights reserved.
//

#import "DemoViewController4.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"

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

@interface DemoViewController4 () <GLKViewDelegate>
{
    GLint _filterPositionAttribute, _filterTextureCoordinateAttribute;
    GLint _filterInputTextureUniform;
    GLint _filterTransformMatrix;
}
@property (nonatomic, strong) UISegmentedControl *segment;
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) GLProgram *program;

@property (nonatomic, assign) GLKMatrix4 matrix;

@property (nonatomic, assign) CGPoint scaleConstant; // 缩放系数
@property (nonatomic, assign) CGPoint translateConstant; // 平移系数
@property (nonatomic, assign) CGPoint translatePoint; // 平移

@property (nonatomic, assign) float degree; // 旋转
@property (nonatomic, assign) float scale; // 缩放

@end

@implementation DemoViewController4

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.scaleConstant = CGPointMake(0.01, 0.01);
        self.translateConstant = CGPointMake(0.01, 0.01);
        self.translatePoint = CGPointMake(1.0, 0.0);
        self.degree = 0.0;
        self.scale = 1.0;
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.segment = [[UISegmentedControl alloc] initWithItems:@[@"平移",@"旋转",@"缩放",@"平移->旋转",@"旋转->平移"]];
    self.segment.frame = CGRectMake(0, 0, 210, 26);
    [self.segment addTarget:self action:@selector(segmentClick:) forControlEvents:UIControlEventValueChanged];
    self.segment.selectedSegmentIndex = 0;
    self.navigationItem.titleView = self.segment;
    
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    // shader
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_4" fragmentShaderFilename:@"shaderf_4"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"inputTextureCoordinate"];
    [self.program link];
    
    _filterPositionAttribute = [self.program attributeIndex:@"position"];
    _filterTextureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    _filterInputTextureUniform = [self.program uniformIndex:@"inputImageTexture"]; // This does assume a name of "inputImageTexture" for the fragment shader
    _filterTransformMatrix = [self.program uniformIndex:@"transformMatrix"];

    // model
    self.matrix = GLKMatrix4MakeRotation(0.0, 0.0, 0.0, 1.0);

    // texture
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"for_test" ofType:@"jpg"];
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil]; // 将纹理坐标原点改为左下角（GLKit加载纹理，默认都是把坐标设置在“左上角”。然而，OpenGL的纹理贴图坐标却是在左下角，这样刚好颠倒）
    self.textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath options:options error:nil];

    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
    [self.displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [self.displayLink invalidate];
    self.displayLink = nil;
}

- (void)segmentClick:(UISegmentedControl *)sender
{
    NSLog(@"%ld",(long)sender.selectedSegmentIndex);
}

- (void)update
{
    if (self.segment.selectedSegmentIndex == 0) {
        // 缩放，便于查看
        CGFloat scale = 0.25;
        GLKMatrix4 scaleMatrix = GLKMatrix4MakeScale(scale, scale, 0.0);

        // 偏移量
        CGFloat maxOffset = 1.0 - 0.25;
        CGFloat minOffset = -1.0 + 0.25;
        CGFloat translateX = self.translatePoint.x + self.translateConstant.x;
        CGFloat translateY = self.translatePoint.y + self.translateConstant.y;
        if (translateX <= minOffset) {
            translateX = minOffset;
            self.translateConstant = CGPointMake(-self.translateConstant.x, self.translateConstant.y);
        }
        if (translateY <= minOffset) {
            translateY = minOffset;
            self.translateConstant = CGPointMake(self.translateConstant.x, -self.translateConstant.y);
        }
        if (translateX >= maxOffset) {
            translateX = maxOffset;
            self.translateConstant = CGPointMake(-self.translateConstant.x, self.translateConstant.y);
        }
        if (translateY >= maxOffset) {
            translateY = maxOffset;
            self.translateConstant = CGPointMake(self.translateConstant.x, -self.translateConstant.y);
        }
        self.translatePoint = CGPointMake(translateX, translateY);
        GLKMatrix4 translationMatrix = GLKMatrix4MakeTranslation(self.translatePoint.x, self.translatePoint.y, 0);
        self.matrix = GLKMatrix4Multiply(translationMatrix, scaleMatrix);
    } else if (self.segment.selectedSegmentIndex == 1) {
        // 设置旋转矩阵
        self.degree += 0.5;
        if (self.degree >= 360.0) {
            self.degree = self.degree - 360.0;
        }
        self.matrix = GLKMatrix4MakeRotation(GLKMathDegreesToRadians(self.degree), 0.0, 0.0, 1.0);
    } else if (self.segment.selectedSegmentIndex == 2) {
        // 设置缩放矩阵
        self.scale += self.scaleConstant.x;
        if (self.scale <= 0.35 || self.scale >= 1.25) {
            self.scaleConstant = CGPointMake(-self.scaleConstant.x, -self.scaleConstant.y);
        }
        // 设置锚点{0.0, -1.0, 0.0}，当前坐标点位置减去锚点坐标，得到平移的距离，当前坐标平移到锚点坐标即可
        self.matrix = GLKMatrix4MakeTranslation(0.0, -1.0, 0.0);
        self.matrix = GLKMatrix4Scale(self.matrix, self.scale, self.scale, 1.0);
        self.matrix = GLKMatrix4Translate(self.matrix, 0.0, 1.0, 0.0);
        // self.matrix = GLKMatrix4MakeScale(self.scale, self.scale, 0.0);
    } else if (self.segment.selectedSegmentIndex == 3) {
        // 缩放，便于查看
        CGFloat scale = 0.25;
        GLKMatrix4 scaleMatrix = GLKMatrix4MakeScale(scale, scale, 0.0);
        // 平移->旋转
        GLKMatrix4 translationMatrix = GLKMatrix4MakeTranslation(1.0, 0, 0);
        GLKMatrix4 rotationMatrix = GLKMatrix4MakeRotation(GLKMathDegreesToRadians(45.0), 0.0, 0.0, 1.0);
        self.matrix = GLKMatrix4Multiply(rotationMatrix, GLKMatrix4Multiply(translationMatrix, scaleMatrix));
        // 等价于
        {
            self.matrix = GLKMatrix4MakeRotation(GLKMathDegreesToRadians(45.0), 0.0, 0.0, 1.0);
            self.matrix = GLKMatrix4Translate(self.matrix, 1.0, 0, 0);
            self.matrix = GLKMatrix4Scale(self.matrix, scale, scale, 1.0);
        }
        // 区别在于：
        // 1.GLKMatrix4Translate，GLKMatrix4Rotate，GLKMatrix4Scale是相对于当前模型坐标系
        // 2.而GLKMatrix4Multiply是相对于世界坐标系，使用矩阵乘法(左乘)做变换
        // 3.世界坐标系的x，y，x的方向是永远不变的，而模型坐标系的x，y，z在使用旋转矩阵GLKMatrix4Rotate后，方向会发生改变
    } else if (self.segment.selectedSegmentIndex == 4) {
        // 缩放，便于查看
        CGFloat scale = 0.25;
        GLKMatrix4 scaleMatrix = GLKMatrix4MakeScale(scale, scale, 0.0);
        // 旋转->平移
        GLKMatrix4 rotationMatrix = GLKMatrix4MakeRotation(GLKMathDegreesToRadians(45.0), 0.0, 0.0, 1.0);
        GLKMatrix4 translationMatrix = GLKMatrix4MakeTranslation(1.0, 0, 0);
        self.matrix = GLKMatrix4Multiply(translationMatrix, GLKMatrix4Multiply(rotationMatrix, scaleMatrix));
        // 等价于
        {
            self.matrix = GLKMatrix4MakeTranslation(1.0, 0, 0);
            self.matrix = GLKMatrix4Rotate(self.matrix, GLKMathDegreesToRadians(45.0), 0.0, 0.0, 1.0);
            self.matrix = GLKMatrix4Scale(self.matrix, scale, scale, 1.0);
        }
        // 区别在于：
        // 1.GLKMatrix4Translate，GLKMatrix4Rotate，GLKMatrix4Scale是相对于当前模型坐标系
        // 2.而GLKMatrix4Multiply是相对于世界坐标系，使用矩阵乘法(左乘)做变换
        // 3.世界坐标系的x，y，x的方向是永远不变的，而模型坐标系的x，y，z在使用旋转矩阵GLKMatrix4Rotate后，方向会发生改变
    }
    [self.glkView display];
}


- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 启用着色器
    [self.program use];
    glEnableVertexAttribArray(_filterPositionAttribute);
    glEnableVertexAttribArray(_filterTextureCoordinateAttribute);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, self.textureInfo.name);
    glUniform1i(_filterInputTextureUniform, 2);
    glUniformMatrix4fv(_filterTransformMatrix, 1, GL_FALSE, (GLfloat *)&_matrix);
    
    glVertexAttribPointer(_filterPositionAttribute, 3, GL_FLOAT, 0, 0, imageVertices);
    glVertexAttribPointer(_filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(_filterPositionAttribute);
    glDisableVertexAttribArray(_filterTextureCoordinateAttribute);
}

- (void)dealloc
{
    [self.displayLink invalidate];
    self.displayLink = nil;
}

@end
