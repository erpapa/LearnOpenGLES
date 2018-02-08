//
//  ViewController.m
//  ColorAlbum
//
//  Created by erpapa on 2018/2/7.
//  Copyright © 2018年 erpapa. All rights reserved.
//

#import "ViewController.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"

GLfloat squareVertexData[] =
{
    0.5f, -0.5f, -0.9f, 1.0f, 0.0f,// 0 右下
    -0.5f, 0.5f, -0.9f, 0.0f, 1.0f,// 1 左上
    -0.5f, -0.5f, -0.9f, 0.0f, 0.0f,// 2 左下
    -0.5f, 0.5f, -0.9f, 0.0f, 1.0f,// 3 左上
    0.5f, 0.5f, -0.9f, 1.0f, 1.0f,// 4 右上
    0.5f, -0.5f, -0.9f, 1.0f, 0.0f,// 5 右下
};

@interface ViewController () <GLKViewDelegate>
{
    GLint filterPositionAttribute, filterTextureCoordinateAttribute;
    GLint filterInputTextureUniform;
    GLint filterTransformMatrix;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) GLProgram *program;
@property (nonatomic, assign) float degree;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.view.backgroundColor = [UIColor whiteColor];
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    // shader
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv" fragmentShaderFilename:@"shaderf"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"inputTextureCoordinate"];
    [self.program link];
    
    filterPositionAttribute = [self.program attributeIndex:@"position"];
    filterTextureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    filterInputTextureUniform = [self.program uniformIndex:@"inputImageTexture"]; // This does assume a name of "inputImageTexture" for the fragment shader
    filterTransformMatrix = [self.program uniformIndex:@"transformMatrix"];
    [self.program use];
    
    // 启用
    glEnableVertexAttribArray(filterPositionAttribute);
    glEnableVertexAttribArray(filterTextureCoordinateAttribute);
    // GLfloat temporaryMatrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    // glUniformMatrix4fv(filterTransformMatrix, 1, GL_FALSE, (GLfloat *)&temporaryMatrix);
    GLKMatrix4 matrix = GLKMatrix4MakeRotation(0.0, 00, 0.0, 1.0);
    glUniformMatrix4fv(filterTransformMatrix, 1, GL_FALSE, (GLfloat *)&matrix);
    
    // texture
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"for_test" ofType:@"jpg"];
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil]; // 将纹理坐标原点改为左下角（GLKit加载纹理，默认都是把坐标设置在“左上角”。然而，OpenGL的纹理贴图坐标却是在左下角，这样刚好颠倒）
    self.textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath options:options error:nil];
    
    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
    [self.displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
}

- (void)update
{
    // 设置旋转矩阵
    self.degree += 0.5;
    if (self.degree >= 360.0) self.degree = 0.0;
    
    //    CATransform3D transform3D = CATransform3DMakeRotation((self.degree / 180.0) * M_PI, 0.0, 0.0, 1.0);
    //    GLfloat temporaryMatrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}; // 原始矩阵
    //    [self convert3DTransform:&transform3D toMatrix:temporaryMatrix];
    //    glUniformMatrix4fv(filterTransformMatrix, 1, GL_FALSE, (GLfloat *)&temporaryMatrix);
    
    GLKMatrix4 matrix = GLKMatrix4MakeRotation((self.degree / 180.0) * M_PI, 00, 0.0, 1.0);
    glUniformMatrix4fv(filterTransformMatrix, 1, GL_FALSE, (GLfloat *)&matrix);
    
    [self.glkView display];
}

- (void)convert3DTransform:(CATransform3D *)transform3D toMatrix:(GLfloat *)matrix;
{
    //    struct CATransform3D
    //    {
    //        CGFloat m11, m12, m13, m14;
    //        CGFloat m21, m22, m23, m24;
    //        CGFloat m31, m32, m33, m34;
    //        CGFloat m41, m42, m43, m44;
    //    };
    
    GLfloat *mappedMatrix = (GLfloat *)matrix;
    
    mappedMatrix[0] = (GLfloat)transform3D->m11;
    mappedMatrix[1] = (GLfloat)transform3D->m12;
    mappedMatrix[2] = (GLfloat)transform3D->m13;
    mappedMatrix[3] = (GLfloat)transform3D->m14;
    mappedMatrix[4] = (GLfloat)transform3D->m21;
    mappedMatrix[5] = (GLfloat)transform3D->m22;
    mappedMatrix[6] = (GLfloat)transform3D->m23;
    mappedMatrix[7] = (GLfloat)transform3D->m24;
    mappedMatrix[8] = (GLfloat)transform3D->m31;
    mappedMatrix[9] = (GLfloat)transform3D->m32;
    mappedMatrix[10] = (GLfloat)transform3D->m33;
    mappedMatrix[11] = (GLfloat)transform3D->m34;
    mappedMatrix[12] = (GLfloat)transform3D->m41;
    mappedMatrix[13] = (GLfloat)transform3D->m42;
    mappedMatrix[14] = (GLfloat)transform3D->m43;
    mappedMatrix[15] = (GLfloat)transform3D->m44;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, self.textureInfo.name);
    
    glUniform1i(filterInputTextureUniform, 2);
    
    static const GLfloat imageVertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f,  1.0f,
        1.0f,  1.0f,
    };
    static const GLfloat noRotationTextureCoordinates[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    glVertexAttribPointer(filterPositionAttribute, 2, GL_FLOAT, 0, 0, imageVertices);
    glVertexAttribPointer(filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

- (void)dealloc
{
    [self.program validate];
    self.program = nil;
}

@end

