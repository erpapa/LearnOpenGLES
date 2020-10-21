//
//  DemoViewController27.m
//  LearnOpenGLES
//
//  Created by apple on 2020/3/12.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController27.h"
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
 * 定向光
 */
struct _DirLight
{
    GLKVector4 direction;
    
    GLKVector4 ambient;
    GLKVector4 diffuse;
    GLKVector4 specular;
};
typedef struct _DirLight DirLight;

/**
 * 点光源
 */
struct _PointLight
{
    GLKVector4 position;
    
    GLKVector4 ambient;
    GLKVector4 diffuse;
    GLKVector4 specular;
    
    float constant;
    float linear;
    float quadratic;
    float padding;
};
typedef struct _PointLight PointLight;

/**
 * 点光源就是一个能够配置位置和衰减的光源
 */
struct _SpotLight
{
    GLKVector4 position;
    GLKVector4 direction;
    
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
typedef struct _SpotLight SpotLight;

@interface DemoViewController27 () <GLKViewDelegate>
{
    GLuint _lightVAO, _lightVBO, _modelVAO, _modelVBO;
    
    GLKVector4 _cubePositions[10];
    GLKVector4 _pointLightPositions[4];
    GLKVector4 _pointLightColors[4];
    
    DirLight _dirLight;
    PointLight _pointLights[4];
    SpotLight _spotLight;
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

@implementation DemoViewController27

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
    self.lightProgram = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_27_0" fragmentShaderFilename:@"shaderf_27_0"];
    [self.lightProgram link];
    
    self.modelProgram = [[GLProgram alloc] initWithVertexShaderFilename:@"shaderv_27_1" fragmentShaderFilename:@"shaderf_27_1"];
    [self.modelProgram link];
    
    // texture
    NSString *diffuseFilePath = [[NSBundle mainBundle] pathForResource:@"container_diffuse" ofType:@"jpg"];
    self.diffuseTextureInfo = [GLKTextureLoader textureWithContentsOfFile:diffuseFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    NSString *specularFilePath = [[NSBundle mainBundle] pathForResource:@"container_specular" ofType:@"jpg"];
    self.specularTextureInfo = [GLKTextureLoader textureWithContentsOfFile:specularFilePath options:[NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil] error:nil];
    
    // positions
    _cubePositions[0] = GLKVector4Make(0.0f, 0.0f,  0.0f, 1.0f);
    _cubePositions[1] = GLKVector4Make(2.0f, 5.0f, -15.0f, 1.0f);
    _cubePositions[2] = GLKVector4Make(-1.5f, -2.2f, -2.5f, 1.0f);
    _cubePositions[3] = GLKVector4Make(-3.8f, -2.0f, -12.3f, 1.0f);
    _cubePositions[4] = GLKVector4Make(2.4f, -0.4f, -3.5f, 1.0f);
    _cubePositions[5] = GLKVector4Make(-1.7f, 3.0f, -7.5f, 1.0f);
    _cubePositions[6] = GLKVector4Make(1.3f, -2.0f, -2.5f, 1.0f);
    _cubePositions[7] = GLKVector4Make(1.5f, 2.0f, -2.5f, 1.0f);
    _cubePositions[8] = GLKVector4Make(1.5f, 0.2f, -1.5f, 1.0f);
    _cubePositions[9] = GLKVector4Make(-1.3f, 1.0f, -1.5f, 1.0f);

    _pointLightPositions[0] = GLKVector4Make(0.7f, 0.2f, 2.0f, 1.0f);
    _pointLightPositions[1] = GLKVector4Make(2.3f, -3.3f, -4.0f, 1.0f);
    _pointLightPositions[2] = GLKVector4Make(-4.0f, 2.0f, -12.0f, 1.0f);
    _pointLightPositions[3] = GLKVector4Make(0.0f, 0.0f, -3.0f, 1.0f);
    
    _pointLightColors[0] = GLKVector4Make(0.7f, 0.2f, 2.0f, 1.0f);
    _pointLightColors[1] = GLKVector4Make(1.0f, 0.0f, 0.0f, 1.0f);
    _pointLightColors[2] = GLKVector4Make(1.0f, 1.0, 0.0, 1.0f);
    _pointLightColors[3] = GLKVector4Make(0.2f, 0.2f, 1.0f, 1.0f);
    
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
    
    // 摄像机
    _camera.position = GLKVector4Make(0.0f, 0.0f, 3.0f, 1.0);
    // 设置摄像机在(0.0, 0.0, 3.0)坐标，看向(0，0，0)点。Y轴正向为摄像机顶部指向的方向
    _camera.view = GLKMatrix4MakeLookAt(_camera.position.x, _camera.position.y, _camera.position.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // 使用透视投影矩阵，视场角设置为90°
    _camera.projection = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90.0f), 1.0f, 0.1f, 100.0f);
        
    // 灯光
    // dirLight
    _dirLight.direction = GLKVector4Make(-0.2f, -1.0f, -0.3f, 1.0f);
    _dirLight.ambient = GLKVector4Make(0.05f, 0.05f, 0.05f, 1.0f);
    _dirLight.diffuse = GLKVector4Make(0.4f, 0.4f, 0.4f, 1.0f);
    _dirLight.specular = GLKVector4Make(0.5f, 0.5f, 0.5f, 1.0f);
    
    // pointLights
    for (int i = 0; i < 4; i++) {
        _pointLights[i].position = _pointLightPositions[i];
        _pointLights[i].ambient = GLKVector4Make(_pointLightColors[i].x * 0.1, _pointLightColors[i].y * 0.1, _pointLightColors[i].z * 0.1, 1.0f); // GLKVector4Make(0.05f, 0.05f, 0.05f, 1.0f);
        _pointLights[i].diffuse = _pointLightColors[i]; // GLKVector4Make(0.8f, 0.8f, 0.8f, 1.0f);
        _pointLights[i].specular = _pointLightColors[i];// GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f);
        _pointLights[i].constant = 1.0; // 衰减常数项
        _pointLights[i].linear = 0.09; // 衰减一次项
        _pointLights[i].quadratic = 0.032; // 衰减二次项
    }
    
    // spotLight
    _spotLight.position = _camera.position;
    _spotLight.direction = GLKVector4Negate(_camera.position);
    _spotLight.ambient = GLKVector4Make(0.0f, 0.0f, 0.0f, 1.0f);
    _spotLight.diffuse = GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f);
    _spotLight.specular = GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f);
    _spotLight.constant = 1.0; // 衰减常数项
    _spotLight.linear = 0.09; // 衰减一次项
    _spotLight.quadratic = 0.032; // 衰减二次项
    _spotLight.cutOff = cosf(GLKMathDegreesToRadians(12.5)); // 内切光角是12.5
    _spotLight.outerCutOff = cosf(GLKMathDegreesToRadians(17.5)); // 外切光角是17.5
        
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
    _camera.position = GLKVector4Make(3.0 * cosf(mediaTime), 0.0, 3.0 * sinf(mediaTime), 1.0);
    _camera.view = GLKMatrix4MakeLookAt(_camera.position.x, _camera.position.y, _camera.position.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    _spotLight.position = _camera.position;
    _spotLight.direction = GLKVector4Negate(_camera.position);

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
        
        glUniformMatrix4fv([self.lightProgram uniformIndex:@"view"], 1, GL_FALSE, (GLfloat *)&_camera.view);
        glUniformMatrix4fv([self.lightProgram uniformIndex:@"projection"], 1, GL_FALSE, (GLfloat *)&_camera.projection);
        
        for (int i = 0; i < 4; i++) {
            GLKMatrix4 scale = GLKMatrix4MakeScale(0.2f, 0.2f, 0.2f);
            GLKMatrix4 translation = GLKMatrix4MakeTranslation(_pointLightPositions[i].x, _pointLightPositions[i].y, _pointLightPositions[i].z);
            GLKMatrix4 lightMatrix = GLKMatrix4Multiply(translation, scale);
            glUniformMatrix4fv([self.lightProgram uniformIndex:@"model"], 1, GL_FALSE, (GLfloat *)&lightMatrix);
            
            // objectColor、ambientColor
            glUniform3f([self.lightProgram uniformIndex:@"objectColor"], _pointLights[i].specular.x, _pointLights[i].specular.y, _pointLights[i].specular.z);
            glUniform3f([self.lightProgram uniformIndex:@"ambientColor"], 1.0, 1.0, 1.0);
            
            glBindVertexArray(_lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }
    }
    // 2.绘制物体
    {
        [self.modelProgram use];
        
        // bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, self.diffuseTextureInfo.name);
        glUniform1i([self.modelProgram uniformIndex:@"material.diffuse"], 0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, self.specularTextureInfo.name);
        glUniform1i([self.modelProgram uniformIndex:@"material.specular"], 1);
        
        glUniform1f([self.modelProgram uniformIndex:@"material.shininess"], 32.0);
        
        // light properties
        glUniform4f([self.modelProgram uniformIndex:@"dirLight.direction"], _dirLight.direction.x, _dirLight.direction.y, _dirLight.direction.z, _dirLight.direction.w);
        glUniform4f([self.modelProgram uniformIndex:@"dirLight.ambient"], _dirLight.ambient.x, _dirLight.ambient.y, _dirLight.ambient.z, _dirLight.ambient.w);
        glUniform4f([self.modelProgram uniformIndex:@"dirLight.diffuse"], _dirLight.diffuse.x, _dirLight.diffuse.y, _dirLight.diffuse.z, _dirLight.diffuse.w);
        glUniform4f([self.modelProgram uniformIndex:@"dirLight.specular"], _dirLight.specular.x, _dirLight.specular.y, _dirLight.specular.z, _dirLight.specular.w);
        
        for (int i = 0; i < 4; i++) {
            glUniform4f([self.modelProgram uniformIndex:[NSString stringWithFormat:@"pointLights[%d].position", i]], _pointLights[i].position.x, _pointLights[i].position.y, _pointLights[i].position.z, _pointLights[i].position.w);
            glUniform4f([self.modelProgram uniformIndex:[NSString stringWithFormat:@"pointLights[%d].ambient", i]], _pointLights[i].ambient.x, _pointLights[i].ambient.y, _pointLights[i].ambient.z, _pointLights[i].ambient.w);
            glUniform4f([self.modelProgram uniformIndex:[NSString stringWithFormat:@"pointLights[%d].diffuse", i]], _pointLights[i].diffuse.x, _pointLights[i].diffuse.y, _pointLights[i].diffuse.z, _pointLights[i].diffuse.w);
            glUniform4f([self.modelProgram uniformIndex:[NSString stringWithFormat:@"pointLights[%d].specular", i]], _pointLights[i].specular.x, _pointLights[i].specular.y, _pointLights[i].specular.z, _pointLights[i].specular.w);
            glUniform1f([self.modelProgram uniformIndex:[NSString stringWithFormat:@"pointLights[%d].constant", i]], _pointLights[i].constant);
            glUniform1f([self.modelProgram uniformIndex:[NSString stringWithFormat:@"pointLights[%d].linear", i]], _pointLights[i].linear);
            glUniform1f([self.modelProgram uniformIndex:[NSString stringWithFormat:@"pointLights[%d].quadratic", i]], _pointLights[i].quadratic);
        }
        
        glUniform4f([self.modelProgram uniformIndex:@"spotLight.position"], _spotLight.position.x, _spotLight.position.y, _spotLight.position.z, _spotLight.position.w);
        glUniform4f([self.modelProgram uniformIndex:@"spotLight.direction"], _spotLight.direction.x, _spotLight.direction.y, _spotLight.direction.z, _spotLight.direction.w);
        glUniform4f([self.modelProgram uniformIndex:@"spotLight.ambient"], _spotLight.ambient.x, _spotLight.ambient.y, _spotLight.ambient.z, _spotLight.ambient.w);
        glUniform4f([self.modelProgram uniformIndex:@"spotLight.diffuse"], _spotLight.diffuse.x, _spotLight.diffuse.y, _spotLight.diffuse.z, _spotLight.diffuse.w);
        glUniform4f([self.modelProgram uniformIndex:@"spotLight.specular"], _spotLight.specular.x, _spotLight.specular.y, _spotLight.specular.z, _spotLight.specular.w);
        glUniform1f([self.modelProgram uniformIndex:@"spotLight.constant"], _spotLight.constant);
        glUniform1f([self.modelProgram uniformIndex:@"spotLight.linear"], _spotLight.linear);
        glUniform1f([self.modelProgram uniformIndex:@"spotLight.quadratic"], _spotLight.quadratic);
        glUniform1f([self.modelProgram uniformIndex:@"spotLight.cutOff"], _spotLight.cutOff);
        glUniform1f([self.modelProgram uniformIndex:@"spotLight.outerCutOff"], _spotLight.outerCutOff);
        
        // camera
        glUniform3f([self.modelProgram uniformIndex:@"camera.position"], _camera.position.x, _camera.position.y, _camera.position.z);
        glUniformMatrix4fv([self.modelProgram uniformIndex:@"camera.view"], 1, GL_FALSE, (GLfloat *)&_camera.view);
        glUniformMatrix4fv([self.modelProgram uniformIndex:@"camera.projection"], 1, GL_FALSE, (GLfloat *)&_camera.projection);
        
        // draw
        for (int i = 0; i < 10; i++) {
            float angle = 20.0f * i;
            GLKMatrix4 rotation = GLKMatrix4MakeRotation(GLKMathDegreesToRadians(angle), 1.0f, 0.3f, 0.5f);
            GLKMatrix4 translation = GLKMatrix4MakeTranslation(_cubePositions[i].x, _cubePositions[i].y, _cubePositions[i].z);
            GLKMatrix4 modelMatrix = GLKMatrix4Multiply(translation, rotation);
            glUniformMatrix4fv([self.modelProgram uniformIndex:@"model_matrix"], 1, GL_FALSE, (GLfloat *)&modelMatrix);
            
            glBindVertexArray(_modelVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }
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
}

@end
