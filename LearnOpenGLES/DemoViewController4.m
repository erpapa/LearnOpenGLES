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

@interface DemoViewController4 () <GLKViewDelegate>
{
    GLint filterPositionAttribute, filterTextureCoordinateAttribute;
    GLint filterInputTextureUniform;
    GLint filterTransformMatrix;
}
@property (nonatomic, strong) UISegmentedControl *segment;
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) GLProgram *program;

@property (nonatomic, assign) GLKMatrix4 matrix;

@property (nonatomic, assign) CGPoint translateConstant; // 平移系数
@property (nonatomic, assign) CGPoint translatePoint; // 平移

@property (nonatomic, assign) float degree; // 旋转

@property (nonatomic, assign) float scaleConstant; // 系数
@property (nonatomic, assign) float scale; // 缩放

@end

@implementation DemoViewController4

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.translateConstant = CGPointMake(0.05, 0.05);
        self.translatePoint = CGPointMake(1.0, 0.0);
        self.degree = 0.0;
        self.scaleConstant = -0.01;
        self.scale = 1.0;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.segment = [[UISegmentedControl alloc] initWithItems:@[@"平移",@"旋转",@"缩放"]];
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
    
    filterPositionAttribute = [self.program attributeIndex:@"position"];
    filterTextureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    filterInputTextureUniform = [self.program uniformIndex:@"inputImageTexture"]; // This does assume a name of "inputImageTexture" for the fragment shader
    filterTransformMatrix = [self.program uniformIndex:@"transformMatrix"];
    self.matrix = GLKMatrix4MakeRotation(0.0, 0.0, 0.0, 1.0);
    [self.program use];
    
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

- (void)update
{
    if (self.segment.selectedSegmentIndex == 0) {
        // 缩放，便于查看
        CGFloat scale = 0.25;
        // 重新计算最大最小值，得到{-3.0,3.0}
        CGFloat maxOffset = 1.0 / scale - 1.0;
        CGFloat minOffset = -maxOffset;
        CGFloat offsetX = self.translatePoint.x + self.translateConstant.x;
        CGFloat offsetY = self.translatePoint.y + self.translateConstant.y;
        if (offsetX <= minOffset) {
            offsetX = minOffset;
            self.translateConstant = CGPointMake(-self.translateConstant.x, self.translateConstant.y);
        }
        if (offsetY <= minOffset) {
            offsetY = minOffset;
            self.translateConstant = CGPointMake(self.translateConstant.x, -self.translateConstant.y);
        }
        if (offsetX >= maxOffset) {
            offsetX = maxOffset;
            self.translateConstant = CGPointMake(-self.translateConstant.x, self.translateConstant.y);
        }
        if (offsetY >= maxOffset) {
            offsetY = maxOffset;
            self.translateConstant = CGPointMake(self.translateConstant.x, -self.translateConstant.y);
        }
        self.translatePoint = CGPointMake(offsetX, offsetY);
        GLKMatrix4 matrix = GLKMatrix4MakeScale(scale, scale, 0.0); // 先缩放
        self.matrix = GLKMatrix4Translate(matrix, self.translatePoint.x, self.translatePoint.y, 0.0);
    } else if (self.segment.selectedSegmentIndex == 1) {
        // 设置旋转矩阵
        self.degree += 0.5;
        if (self.degree >= 360.0) {
            self.degree = 0.0;
        }
        self.matrix = GLKMatrix4MakeRotation(GLKMathDegreesToRadians(self.degree), 0.0, 0.0, 1.0);
    } else if (self.segment.selectedSegmentIndex == 2) {
        // 设置缩放矩阵
        self.scale += self.scaleConstant;
        if (self.scale <= 0.35 || self.scale >= 1.25) {
            self.scaleConstant = -self.scaleConstant;
        }
        self.matrix = GLKMatrix4MakeScale(self.scale, self.scale, 0.0);
    }
    [self.glkView display];
}


- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 启用
    [self.program use];
    glEnableVertexAttribArray(filterPositionAttribute);
    glEnableVertexAttribArray(filterTextureCoordinateAttribute);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, self.textureInfo.name);
    
    glUniform1i(filterInputTextureUniform, 2);
    glUniformMatrix4fv(filterTransformMatrix, 1, GL_FALSE, (GLfloat *)&_matrix);
    
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
    glVertexAttribPointer(filterPositionAttribute, 3, GL_FLOAT, 0, 0, imageVertices);
    glVertexAttribPointer(filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(filterPositionAttribute);
    glDisableVertexAttribArray(filterTextureCoordinateAttribute);
}

- (void)segmentClick:(UISegmentedControl *)sender
{
    NSLog(@"%ld",(long)sender.selectedSegmentIndex);
}

- (void)dealloc
{
    [self.displayLink invalidate];
    self.displayLink = nil;
    
    [self.program validate];
    self.program = nil;
}

@end
