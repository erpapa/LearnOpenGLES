//
//  DemoViewController7.m
//  LearnOpenGLES
//
//  Created by apple on 2018/10/29.
//  Copyright © 2018 erpapa. All rights reserved.
//

#import "DemoViewController7.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import "GLProgram.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "ftgl/ftgl.h"
#include "poly2tri/poly2tri.h"

struct Vector3df
{
    float x, y, z;
};

struct Tri
{
    Vector3df a, b, c;
};

@interface DemoViewController7 () <GLKViewDelegate>
{
    GLuint VAO, VBO0, VBO1;
    GLint positionAttribute, textureCoordinateAttribute;
    GLKMatrix4 modelMatrix, viewMatrix, projectionMatrix;
    int vert_ount, vert_size;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLKTextureInfo *textureInfo;
@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) GLProgram *program;
@property (nonatomic, assign) float degree; // 旋转

@end

@implementation DemoViewController7

float add_character(std::vector<Tri> &tris, FT_Face face, char ch, int bezier_steps, float extrude, float offset)
{
    static FT_UInt prevCharIndex = 0, curCharIndex = 0;
    static FT_Pos  prev_rsb_delta = 0;
    
    curCharIndex = FT_Get_Char_Index( face, ch );
    if(FT_Load_Glyph( face, curCharIndex, FT_LOAD_DEFAULT ))
        printf("FT_Load_Glyph failed\n");
    
    FT_Glyph glyph;
    if(FT_Get_Glyph( face->glyph, &glyph ))
        printf("FT_Get_Glyph failed\n");
    
    if(glyph->format != FT_GLYPH_FORMAT_OUTLINE) {
        printf("Invalid Glyph Format\n");
        exit(0);
    }
    
    short nCountour = 0;
    nCountour = face->glyph->outline.n_contours;
    
    // int startIndex = 0, endIndex = 0;
    // FT_Outline* o = &face->glyph->outline;
    
    if(FT_HAS_KERNING( face ) && prevCharIndex) {
        FT_Vector  kerning;
        FT_Get_Kerning( face, prevCharIndex, curCharIndex, FT_KERNING_DEFAULT, &kerning );
        offset += kerning.x >> 6;
    }
    
    if ( prev_rsb_delta - face->glyph->lsb_delta >= 32 )
        offset -= 1.0f;
    else if ( prev_rsb_delta - face->glyph->lsb_delta < -32 )
        offset += 1.0f;
    
    prev_rsb_delta = face->glyph->rsb_delta;
    
    ftgl::Vectoriser *vectoriser = new ftgl::Vectoriser(face->glyph, bezier_steps);
    for(size_t c = 0; c < vectoriser->ContourCount(); ++c) {
        const ftgl::Contour* contour = vectoriser->GetContour(c);
        
        for(size_t p = 0; p < contour->PointCount() - 1; ++p) {
            const double* d1 = contour->GetPoint(p);
            const double* d2 = contour->GetPoint(p + 1);
            Tri t1;
            t1.a.x = (d1[0]/64.0f) + offset;
            t1.a.y = d1[1]/64.0f;
            t1.a.z = 0.0f;
            t1.b.x = (d2[0]/64.0f) + offset;
            t1.b.y = d2[1]/64.0f;
            t1.b.z = 0.0f;
            t1.c.x = (d1[0]/64.0f) + offset;
            t1.c.y = d1[1]/64.0f;
            t1.c.z = extrude;
            tris.push_back(t1);
            
            Tri t2;
            t2.a.x = (d1[0]/64.0f) + offset;
            t2.a.y = d1[1]/64.0f;
            t2.a.z = extrude;
            t2.b.x = (d2[0]/64.0f) + offset;
            t2.b.y = d2[1]/64.0f;
            t2.b.z = extrude;
            t2.c.x = (d2[0]/64.0f) + offset;
            t2.c.y = d2[1]/64.0f;
            t2.c.z = 0.0f;
            tris.push_back(t2);
        }
        
        if (contour->GetDirection()) {
            std::vector<p2t::Point*> polyline;
            for(size_t p = 0; p < contour->PointCount(); ++p) {
                const double* d = contour->GetPoint(p);
                polyline.push_back(new p2t::Point((d[0]/64.0f) + offset, d[1]/64.0f));
            }
            
            p2t::CDT* cdt = new p2t::CDT(polyline);
            for(size_t cm = 0; cm < vectoriser->ContourCount(); ++cm) {
                const ftgl::Contour* sm = vectoriser->GetContour(cm);
                if(c != cm && !sm->GetDirection() && sm->IsInside(contour)) {
                    std::vector<p2t::Point*> pl;
                    for(size_t p = 0; p < contour->PointCount(); ++p) {
                        const double* d = contour->GetPoint(p);
                        pl.push_back(new p2t::Point((d[0]/64.0f) + offset, d[1]/64.0f));
                    }
                    cdt->AddHole(pl);
                }
            }
            
            cdt->Triangulate();
            std::vector<p2t::Triangle*> ts = cdt->GetTriangles();
            for(int i = 0; i < ts.size(); i++) {
                p2t::Triangle* ot = ts[i];
                
                Tri t1;
                t1.a.x = ot->GetPoint(0)->x;
                t1.a.y = ot->GetPoint(0)->y;
                t1.a.z = 0.0f;
                t1.b.x = ot->GetPoint(1)->x;
                t1.b.y = ot->GetPoint(1)->y;
                t1.b.z = 0.0f;
                t1.c.x = ot->GetPoint(2)->x;
                t1.c.y = ot->GetPoint(2)->y;
                t1.c.z = 0.0f;
                tris.push_back(t1);
                
                Tri t2;
                t2.a.x = ot->GetPoint(0)->x;
                t2.a.y = ot->GetPoint(0)->y;
                t2.a.z = extrude;
                t2.b.x = ot->GetPoint(1)->x;
                t2.b.y = ot->GetPoint(1)->y;
                t2.b.z = extrude;
                t2.c.x = ot->GetPoint(2)->x;
                t2.c.y = ot->GetPoint(2)->y;
                t2.c.z = extrude;
                tris.push_back(t2);
            }
            delete cdt;
        }
    }
    
    delete vectoriser;
    vectoriser = NULL;
    
    prevCharIndex = curCharIndex;
    float chSize = face->glyph->advance.x >> 6;
    return offset + chSize;
}

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
    self.program = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_7" fragmentShaderFilename:@"shaderf_7"];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"inputTextureCoordinate"];
    [self.program link];
    
    // 顶点
    positionAttribute = [self.program attributeIndex:@"position"];
    textureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    
    NSString *fontPath = [[NSBundle mainBundle] pathForResource:@"hwxk" ofType:@"ttf"];
    const char *char_font = [fontPath UTF8String];
    const char *char_str = "Hi";
    int char_height = 48;
    int bezier_steps = 4;
    float extrude = 16;
    
    FT_Library library;
    if (FT_Init_FreeType( &library ))
        printf("FT_Init_FreeType failed\n");
    
    FT_Face face;
    if (FT_New_Face( library, char_font, 0, &face ))
        printf("FT_New_Face failed (there is probably a problem with your font file\n");
    
    int char_size = char_height << 6;
    FT_Set_Char_Size( face, char_size, char_size, 96, 96);
    
    std::vector<Tri> tris;
    float offset = 0;
    for (int i = 0; i < strlen(char_str); i++) {
        offset = add_character(tris, face, char_str[i], bezier_steps, extrude, offset);
    }
    
    vert_ount = (int)tris.size() * 3;
    vert_size = vert_ount * 3;
    float *vertices = (float *)malloc(sizeof(float) * vert_size);
    for (int i = 0, j = 0; i < tris.size(); i+=1, j+=9) {
        Tri t = tris[i];
        vertices[j] = t.a.x / char_size * 64.0;
        vertices[j + 1] = t.a.y / char_size * 64.0;
        vertices[j + 2] = t.a.z / char_size * 64.0;
        
        vertices[j + 3] = t.b.x / char_size * 64.0;
        vertices[j + 4] = t.b.y / char_size * 64.0;
        vertices[j + 5] = t.b.z / char_size * 64.0;
        
        vertices[j + 6] = t.c.x / char_size * 64.0;
        vertices[j + 7] = t.c.y / char_size * 64.0;
        vertices[j + 8] = t.c.z / char_size * 64.0;
    }
    float texCoords[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    
    // 创建索引缓冲对象
    glGenVertexArraysOES(1, &VAO);
    glGenBuffers(1, &VBO0);
    glGenBuffers(1, &VBO1);
    
    // 绑定VAO
    glBindVertexArrayOES(VAO);
    
    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO0);
    glBufferData(GL_ARRAY_BUFFER, vert_size * sizeof(float), vertices, GL_STATIC_DRAW);
    
    // 位置属性
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttribute);
    
    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    // 纹理
    glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(textureCoordinateAttribute);
    
    // glBindBuffer(GL_ARRAY_BUFFER, 0); // 这个方法将顶点属性指针注册到VBO作为当前绑定顶点对象，然后我们就可以安全的解绑
    glBindVertexArrayOES(0); // 解绑 VAO (这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法)
    glEnable(GL_DEPTH_TEST); // 启用深度测试，必须先设置drawableDepthFormat
    free(vertices);
    
    // texture
    NSString *diffuseFilePath = [[NSBundle mainBundle] pathForResource:@"material" ofType:@"jpg"];
    self.textureInfo = [GLKTextureLoader textureWithContentsOfFile:diffuseFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    
    // 初始化模型矩阵
    modelMatrix = GLKMatrix4Identity;
    // 设置摄像机在(0，0，3)坐标，看向(0，0，0)点。Y轴正向为摄像机顶部指向的方向
    viewMatrix = GLKMatrix4MakeLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
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
    modelMatrix = GLKMatrix4MakeRotation(GLKMathDegreesToRadians(self.degree), -0.3, 1.0, 0.0);
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
    glDrawArrays(GL_TRIANGLES, 0, vert_ount);
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
    if (VBO0) {
        glDeleteBuffers(1, &VBO0);
        VBO0 = 0;
    }
    if (VBO1) {
        glDeleteBuffers(1, &VBO1);
        VBO1 = 0;
    }
}

@end
