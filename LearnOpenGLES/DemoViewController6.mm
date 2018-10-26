//
//  DemoViewController6.m
//  LearnOpenGLES
//
//  Created by apple on 2018/10/25.
//  Copyright © 2018 erpapa. All rights reserved.
//

#import "DemoViewController6.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#include <FTGL/ftgles.h>
#include <FTGL/ftglesGlue.h>
#include "RenderController.h"
#import "GLProgram.h"

@interface DemoViewController6 () <GLKViewDelegate>
{
    FTFont *polygonFont;
    FTFont *textureFont;
    FTFont *outlineFont;
    FTSimpleLayout *simpleLayout;
    float polygonFontViewMatrix[16];
    float textureFontViewMatrix[16];
    float simpleLayoutViewMatrix[16];
    
    GLint filterPositionAttribute, filterTextureCoordAttribute, filterColorAttribute;
    GLint filterCameraUniform, filterAltColorUniform;
    GLint filterInputTextureUniform, filterUseTextureUniform;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) GLProgram *program;

@property (nonatomic, assign) float mover;

@end

@implementation DemoViewController6

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    CGFloat screenWidth = [UIScreen mainScreen].bounds.size.width;
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    
    NSString *fontPath = [[NSBundle mainBundle] pathForResource:@"davlo" ofType:@"otf"];
    polygonFont = new FTPolygonFont([fontPath UTF8String]);
    assert (!polygonFont->Error());
    polygonFont->FaceSize(screenWidth * 0.25f);
    polygonFont->Depth(10.0);
    
    textureFont = new FTTextureFont([fontPath UTF8String]);
    assert (!textureFont->Error());
    textureFont->FaceSize(screenWidth * 0.25f);
    polygonFont->Depth(10.0);
    
    outlineFont = new FTOutlineFont([fontPath UTF8String]);
    assert (!outlineFont->Error());
    outlineFont->FaceSize(screenWidth * 0.25f);
    outlineFont->Depth(10.0);
    
    simpleLayout = new FTSimpleLayout();
    simpleLayout->SetLineLength(screenWidth * [UIScreen mainScreen].scale);
    simpleLayout->SetLineSpacing(10.0);
    simpleLayout->SetFont(outlineFont);
    simpleLayout->SetAlignment(FTGL::ALIGN_CENTER);
    
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.contentScaleFactor = [UIScreen mainScreen].scale;
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    // shader
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_5" fragmentShaderFilename:@"shaderf_5"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"textureCoord"];
    [self.program addAttribute:@"color"];
    [self.program link];
    
    filterPositionAttribute = [self.program attributeIndex:@"position"];
    filterTextureCoordAttribute = [self.program attributeIndex:@"textureCoord"];
    filterColorAttribute = [self.program attributeIndex:@"color"];
    filterCameraUniform = [self.program uniformIndex:@"camera"];
    filterAltColorUniform = [self.program uniformIndex:@"altColor"];
    filterInputTextureUniform = [self.program uniformIndex:@"inputTexture"]; // This does assume a name of "inputImageTexture" for the fragment shader
    filterUseTextureUniform = [self.program uniformIndex:@"useTexture"];
    [self.program use];
    
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
    self.mover += 0.01f;
    float perspectiveMatrix[16];
    aglMatrixPerspectiveFovRH(perspectiveMatrix, 90.0f, 1.0, 0.01f, 1000.0f);

    vec3_t pos, at, up;
    vec3Set(pos, 420, 200, -500.0f);
    vec3Set(at,  420.0f + 100.0f * sinf(self.mover), 200, -1000.0f);
    vec3Set(up,  0.0f, 1.0f, 0.0f);
    
    // Render the polygon font
    aglMatrixLookAtRH(polygonFontViewMatrix, pos, at, up);
    aglMatrixMultiply(polygonFontViewMatrix, polygonFontViewMatrix, perspectiveMatrix);
    
    // Render the texture font
    const float moveUpBy = 300.0f;
    vec3Set(at, at[0], at[1] - moveUpBy, at[2]);
    vec3Set(pos, pos[0], pos[1] - moveUpBy, pos[2]);
    aglMatrixLookAtRH(textureFontViewMatrix, pos, at, up);
    aglMatrixMultiply(textureFontViewMatrix, textureFontViewMatrix, perspectiveMatrix);
    
    // SimpleLayout
    vec3Set(at, at[0], at[1] - moveUpBy, at[2]);
    vec3Set(pos, pos[0], pos[1] - moveUpBy, pos[2]);
    aglMatrixLookAtRH(simpleLayoutViewMatrix, pos, at, up);
    aglMatrixMultiply(simpleLayoutViewMatrix, simpleLayoutViewMatrix, perspectiveMatrix);
    
    [self.glkView display];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    [self.program use];
    ftglBindPositionAttribute(filterPositionAttribute);
    ftglBindColorAttribute(filterColorAttribute);
    ftglBindTextureAttribute(filterTextureCoordAttribute);
    
    // Render the polygon font
    glUniformMatrix4fv(filterCameraUniform, 1, GL_FALSE, polygonFontViewMatrix);
    glUniform4f(filterAltColorUniform, 0.3f, 0.7f, 1.0f, 1.0f);
    glUniform1i(filterUseTextureUniform, 0);
    if (polygonFont) {
        polygonFont->Render("Polygon Font");
    }

    // Render the texture font
    glUniformMatrix4fv(filterCameraUniform, 1, GL_FALSE, textureFontViewMatrix);
    glUniform4f(filterAltColorUniform, 1.0f, 1.0f, 0.0f, 1.0f);
    glUniform1i(filterUseTextureUniform, 1);
    if (textureFont) {
        textureFont->Render("Texture Font");
    }
    
    // Render the Simple Layout
    glUniformMatrix4fv(filterCameraUniform, 1, GL_FALSE, simpleLayoutViewMatrix);
    glUniform4f(filterAltColorUniform, 0.5f, 0.5f, 0.5f, 1.0f);
    glUniform1i(filterUseTextureUniform, 0);
    if (simpleLayout) {
        simpleLayout->Render("Simple Layout", -1, FTPoint(), FTGL::RENDER_FRONT);
    }
    
    glDisableVertexAttribArray(filterPositionAttribute);
    glDisableVertexAttribArray(filterColorAttribute);
    glDisableVertexAttribArray(filterTextureCoordAttribute);
}

- (void)dealloc
{
    [self.program validate];
    self.program = nil;
    
    if (polygonFont) {
        delete polygonFont;
        polygonFont = nullptr;
    }
    if (textureFont) {
        delete textureFont;
        textureFont = nullptr;
    }
    if (outlineFont) {
        delete outlineFont;
        outlineFont = nullptr;
    }
    if (simpleLayout) {
        delete simpleLayout;
        simpleLayout = nullptr;
    }
}

@end
