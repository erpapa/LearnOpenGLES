//
//  DemoViewController25.m
//  LearnOpenGLES
//
//  Created by apple on 2020/3/12.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController26.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>
#import "GLProgram.h"

// 位置和法线
static GLfloat boxVertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

struct _Camera
{
    GLKVector4 position;
    GLKMatrix4 view;
    GLKMatrix4 projection;
};
typedef struct _Camera Camera;

/**
 * 点光源就是一个能够配置位置和衰减的光源
 */
struct _Light
{
    GLKVector4 position;
    GLKVector4 direction;
    
    GLKVector4 color;
    GLKVector4 ambient;
    GLKVector4 diffuse;
    GLKVector4 specular;
    
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
    float padding[3];
};
typedef struct _Light Light;

@interface DemoViewController26 () <GLKViewDelegate>
{
    GLuint _lightVAO, _lightVBO, _modelVAO, _modelVBO;
    GLKMatrix4 _lightMatrix, _modelMatrix;
    
    GLuint _material_buffer;
    GLuint _light_buffer;
    GLuint _camera_buffer;
    Light _light;
    Camera _camera;
}
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) GLProgram *lightProgram;
@property (nonatomic, strong) GLProgram *modelProgram;
@property (nonatomic, strong) GLKTextureInfo *diffuseTextureInfo;
@property (nonatomic, strong) GLKTextureInfo *specularTextureInfo;
@property (nonatomic, strong) CADisplayLink *displayLink;

@end

@implementation DemoViewController26

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    // shader
    self.lightProgram = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_26_0" fragmentShaderFilename:@"shaderf_26_0"];
    [self.lightProgram link];
    
    self.modelProgram = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_26_1" fragmentShaderFilename:@"shaderf_26_1"];
    [self.modelProgram link];
    
    // texture
    NSString *diffuseFilePath = [[NSBundle mainBundle] pathForResource:@"container_diffuse" ofType:@"jpg"];
    self.diffuseTextureInfo = [GLKTextureLoader textureWithContentsOfFile:diffuseFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    NSString *specularFilePath = [[NSBundle mainBundle] pathForResource:@"container_specular" ofType:@"jpg"];
    self.specularTextureInfo = [GLKTextureLoader textureWithContentsOfFile:specularFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    
    // 1.创建灯光
    {
        glGenVertexArrays(1, &_lightVAO);
        glGenBuffers(1, &_lightVBO);
        
        glBindVertexArray(_lightVAO);
        glBindBuffer(GL_ARRAY_BUFFER, _lightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        
        // glBindBuffer(GL_ARRAY_BUFFER, 0); // 不可以解绑，此时VAO管理着它们
        glBindVertexArray(0); // 解绑VAO（这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法）
    }
    // 2.创建物体
    {
        glGenVertexArrays(1, &_modelVAO);
        glGenBuffers(1, &_modelVBO);
        
        glBindVertexArray(_modelVAO);
        glBindBuffer(GL_ARRAY_BUFFER, _modelVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        // glBindBuffer(GL_ARRAY_BUFFER, 0); // 不可以解绑，此时VAO管理着它们
        glBindVertexArray(0); // 解绑VAO（这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法）
    }
    // 3.UBO
    {
//        // 3.1.material
//        GLuint material_point = 1;
//        // 获取Uniform Block的索引值
//        GLuint material_index = glGetUniformBlockIndex(self.modelProgram.program, "Material");
//        //将Uniform Block的索引值和binding point关联
//        glUniformBlockBinding(self.modelProgram.program, material_index, material_point);
//
//        glGenBuffers(1, &_material_buffer);
//        glBindBuffer(GL_UNIFORM_BUFFER, _material_buffer);
//        // 设置UBO存储的数据（用来给Uniform Block中变量赋值）
//        glBufferData(GL_UNIFORM_BUFFER, offsetof(Material, padding), NULL, GL_DYNAMIC_DRAW);
//        // 将buffer与point关联
//        glBindBufferBase(GL_UNIFORM_BUFFER, material_point, _material_buffer);
//        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        
        // 3.2.light
        GLuint light_point = 2;
        // 获取Uniform Block的索引值
        GLuint light_index = glGetUniformBlockIndex(self.modelProgram.program, "Light");
        //将Uniform Block的索引值和binding point关联
        glUniformBlockBinding(self.modelProgram.program, light_index, light_point);
        
        glGenBuffers(1, &_light_buffer);
        glBindBuffer(GL_UNIFORM_BUFFER, _light_buffer);
        // 设置UBO存储的数据（用来给Uniform Block中变量赋值）
        glBufferData(GL_UNIFORM_BUFFER, offsetof(Light, padding), NULL, GL_DYNAMIC_DRAW);
        // 将buffer与point关联
        glBindBufferBase(GL_UNIFORM_BUFFER, light_point, _light_buffer);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        
        // 3.3.camera
        GLuint camera_point = 3;
        // 获取Uniform Block的索引值
        GLuint camera_index = glGetUniformBlockIndex(self.modelProgram.program, "Camera");
        //将Uniform Block的索引值和binding point关联
        glUniformBlockBinding(self.modelProgram.program, camera_index, camera_point);
        
        glGenBuffers(1, &_camera_buffer);
        glBindBuffer(GL_UNIFORM_BUFFER, _camera_buffer);
        // 设置UBO存储的数据（用来给Uniform Block中变量赋值）
        glBufferData(GL_UNIFORM_BUFFER, sizeof(Camera), NULL, GL_DYNAMIC_DRAW);
        // 将buffer与point关联
        glBindBufferBase(GL_UNIFORM_BUFFER, camera_point, _camera_buffer);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    
    // 初始化模型矩阵
    _modelMatrix = GLKMatrix4Identity;
    
    // 灯光
    _light.position = GLKVector4Make(0.0, 1.0, -1.0, 1.0);
    _light.direction = GLKVector4Make(0.0, -1.0, 1.0, 0.0);
    _light.constant = 1.0; // 衰减常数项
    _light.linear = 0.09; // 衰减一次项
    _light.quadratic = 0.032; // 衰减二次项
    _light.cutOff = cosf(GLKMathDegreesToRadians(12.5)); // 内切光角是12.5
    _light.outerCutOff = cosf(GLKMathDegreesToRadians(17.5)); // 外切光角是17.5
    _lightMatrix = GLKMatrix4Multiply(GLKMatrix4MakeTranslation(_light.position.x, _light.position.y, _light.position.z), GLKMatrix4MakeScale(0.25, 0.25, 0.25));
    
    // 摄像机
    _camera.position = GLKVector4Make(1.5, 1.5, 1.5, 1.0);
    // 设置摄像机在(1.5, 1.5, 1.5)坐标，看向(0，0，0)点。Y轴正向为摄像机顶部指向的方向
    _camera.view = GLKMatrix4MakeLookAt(_camera.position.x, _camera.position.y, _camera.position.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // 使用透视投影矩阵，视场角设置为90°
    _camera.projection = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90.0f), 1.0f, 0.1f, 100.0f);
    
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
    // 更新摄像机位置（沿Y轴顺时针转动摄像机，视野里箱子逆时针转动）
    CFTimeInterval mediaTime = CACurrentMediaTime() * 0.25;
    _camera.position = GLKVector4Make(1.5 * cosf(mediaTime), 1.5, 1.5 * sinf(mediaTime), 1.0);
    _camera.view = GLKMatrix4MakeLookAt(_camera.position.x, _camera.position.y, _camera.position.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    _light.color = GLKVector4Make(1.0, 1.0, 1.0, 1.0);
    _light.ambient = GLKVector4Multiply(_light.color, GLKVector4Make(0.1f, 0.1f, 0.1f, 1.0f));
    _light.diffuse = GLKVector4Multiply(_light.color, GLKVector4Make(0.5f, 0.5f, 0.5f, 1.0f));
    _light.specular = GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f);
    
    [self.glkView display];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 启用深度测试，必须先设置drawableDepthFormat
    glEnable(GL_DEPTH_TEST);
    // 当深度值小于等于的时候绘制，默认是GL_LESS
    glDepthFunc(GL_LEQUAL);
    
    // 1.绘制灯光
    {
        [self.lightProgram use];
        // model、view、projection
        glUniformMatrix4fv([self.lightProgram uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&_lightMatrix);
        glUniformMatrix4fv([self.lightProgram uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&_camera.view);
        glUniformMatrix4fv([self.lightProgram uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&_camera.projection);
        
        // objectColor、ambientColor
        glUniform3f([self.lightProgram uniformIndex:@"objectColor"], _light.color.x, _light.color.y, _light.color.z);
        glUniform3f([self.lightProgram uniformIndex:@"ambientColor"], 1.0, 1.0, 1.0);
        
        glBindVertexArray(_lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
    // 2.绘制物体
    {
        [self.modelProgram use];
        
        // model
        glUniformMatrix4fv([self.modelProgram uniformIndex:@"model_matrix"], 1, GL_FALSE, (GLfloat *)&_modelMatrix);
        
        // bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, self.diffuseTextureInfo.name);
        glUniform1i([self.modelProgram uniformIndex:@"material.diffuse"], 0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, self.specularTextureInfo.name);
        glUniform1i([self.modelProgram uniformIndex:@"material.specular"], 1);
        
        glUniform1f([self.modelProgram uniformIndex:@"material.shininess"], 32.0);
        
        // bind ubo
//        glBindBuffer(GL_UNIFORM_BUFFER, _material_buffer);
//        glBufferSubData(GL_UNIFORM_BUFFER, 0, offsetof(Material, padding), &_material);
        glBindBuffer(GL_UNIFORM_BUFFER, _camera_buffer);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Camera), &_camera);
        glBindBuffer(GL_UNIFORM_BUFFER, _light_buffer);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, offsetof(Light, padding), &_light);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        
        // draw
        glBindVertexArray(_modelVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
    
    glDisable(GL_DEPTH_TEST);
}

- (void)dealloc
{
    if (_lightVAO) {
        glDeleteVertexArrays(1, &_lightVAO);
        _lightVAO = 0;
    }
    if (_lightVBO) {
        glDeleteBuffers(1, &_lightVBO);
        _lightVBO = 0;
    }
    if (_modelVAO) {
        glDeleteVertexArrays(1, &_modelVAO);
        _modelVAO = 0;
    }
    if (_modelVBO) {
        glDeleteBuffers(1, &_modelVBO);
        _modelVBO = 0;
    }
    if (_material_buffer) {
        glDeleteBuffers(1, &_material_buffer);
        _material_buffer = 0;
    }
    if (_light_buffer) {
        glDeleteBuffers(1, &_light_buffer);
        _light_buffer = 0;
    }
    if (_camera_buffer) {
        glDeleteBuffers(1, &_camera_buffer);
        _camera_buffer = 0;
    }
}

@end
