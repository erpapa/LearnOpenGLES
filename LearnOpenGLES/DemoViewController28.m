//
//  DemoViewController28.m
//  LearnOpenGLES
//
//  Created by apple on 2019/8/29.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController28.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <GLKit/GLKit.h>
#import "GLProgram.h"
#import "DemoFluidUtils.h"

#pragma mark - ViewController

@interface DemoViewController28 () <GLKViewDelegate>

@property (nonatomic, assign) FluidConfig config;
@property (nonatomic, assign) FluidExtension extension;
@property (nonatomic, strong) NSMutableArray *pointers;
@property (nonatomic, strong) NSMutableArray *splatStack;
@property (nonatomic, strong) NSMutableArray *bloomFramebuffers;

@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) GLKView *glkView;
@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) GLKTextureInfo *ditheringTexture;

@property (nonatomic, assign) int canvasWidth;
@property (nonatomic, assign) int canvasHeight;
@property (nonatomic, assign) CFTimeInterval lastUpdateTime;
@property (nonatomic, assign) CFTimeInterval colorUpdateTimer;

@property (nonatomic, strong) FluidDoubleFrameBuffer *dye;
@property (nonatomic, strong) FluidDoubleFrameBuffer *velocity;
@property (nonatomic, strong) FluidFrameBuffer *divergence;
@property (nonatomic, strong) FluidFrameBuffer *curl;
@property (nonatomic, strong) FluidDoubleFrameBuffer *pressure;
@property (nonatomic, strong) FluidFrameBuffer *bloom;
@property (nonatomic, strong) FluidFrameBuffer *sunrays;
@property (nonatomic, strong) FluidFrameBuffer *sunraysTemp;
@property (nonatomic, strong) FluidFrameBuffer *displayBuffer;

@property (nonatomic, strong) FluidProgram *blurProgram;
@property (nonatomic, strong) FluidProgram *defaultProgram;
@property (nonatomic, strong) FluidProgram *clearProgram;
@property (nonatomic, strong) FluidProgram *colorProgram;
@property (nonatomic, strong) FluidProgram *checkerboardProgram;
@property (nonatomic, strong) FluidProgram *bloomPrefilterProgram;
@property (nonatomic, strong) FluidProgram *bloomBlurProgram;
@property (nonatomic, strong) FluidProgram *bloomFinalProgram;
@property (nonatomic, strong) FluidProgram *sunraysMaskProgram;
@property (nonatomic, strong) FluidProgram *sunraysProgram;
@property (nonatomic, strong) FluidProgram *splatProgram;
@property (nonatomic, strong) FluidProgram *advectionProgram;
@property (nonatomic, strong) FluidProgram *divergenceProgram;
@property (nonatomic, strong) FluidProgram *curlProgram;
@property (nonatomic, strong) FluidProgram *vorticityProgram;
@property (nonatomic, strong) FluidProgram *pressureProgram;
@property (nonatomic, strong) FluidProgram *gradienSubtractProgram;
@property (nonatomic, strong) FluidProgram *displayMaterial;

@end

@implementation DemoViewController28

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        _config = (FluidConfig) {
            .SIM_RESOLUTION = 128,
            .DYE_RESOLUTION = 512,
            .CAPTURE_RESOLUTION = 512,
            .DENSITY_DISSIPATION = 1,
            .VELOCITY_DISSIPATION = 0.2,
            .PRESSURE = 0.8,
            .PRESSURE_ITERATIONS = 20,
            .CURL = 30,
            .SPLAT_RADIUS = 5,
            .SPLAT_FORCE = 2000,
            .SHADING = YES,
            .COLORFUL = YES,
            .COLOR_UPDATE_SPEED = 10,
            .PAUSED = NO,
            .BACK_COLOR = GLKVector3Make(0.0, 0.0, 0.0),
            .TRANSPARENT = NO,
            .BLOOM = YES,
            .BLOOM_ITERATIONS = 8,
            .BLOOM_RESOLUTION = 256,
            .BLOOM_INTENSITY = 0.8,
            .BLOOM_THRESHOLD = 0.6,
            .BLOOM_SOFT_KNEE = 0.7,
            .SUNRAYS = YES,
            .SUNRAYS_RESOLUTION = 196,
            .SUNRAYS_WEIGHT = 1.0
        };
        _extension = (FluidExtension) {
            .formatRGBA = (FluidFormat) {GL_RGBA, GL_RGBA},
            .formatRG = (FluidFormat) {GL_RGBA, GL_RGBA},
            .formatR = (FluidFormat) {GL_RGBA, GL_RGBA},
            .halfFloatTexType = GL_HALF_FLOAT_OES,
            .supportLinearFiltering = YES
        };
        FluidPointer *pointer = [[FluidPointer alloc] init];
        self.pointers = [NSMutableArray arrayWithObjects:pointer, nil];
        self.splatStack = [NSMutableArray array];
        self.bloomFramebuffers = [NSMutableArray array];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    self.glkView = [[GLKView alloc] initWithFrame:CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds)) context:self.eglContext];
    self.glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    self.glkView.delegate = self;
    [self.view addSubview:self.glkView];
    [EAGLContext setCurrentContext:self.eglContext];
    
    self.canvasWidth = CGRectGetWidth(self.glkView.bounds) * self.glkView.contentScaleFactor;
    self.canvasHeight = CGRectGetHeight(self.glkView.bounds) * self.glkView.contentScaleFactor;
    self.lastUpdateTime = CACurrentMediaTime();
    self.colorUpdateTimer = 0.0;
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"fluid_dithering" ofType:@"png"];
    self.ditheringTexture = [GLKTextureLoader textureWithContentsOfFile:filePath options:NULL error:nil];
    
    [self setupProgram];
    [self updateKeywords];
    [self setupFramebuffers];
    // [self multipleSplats:1 + arc4random() % 5];
    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
    [self.displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(willEnterBackground:) name:UIApplicationWillResignActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(willEnterForeground:) name:UIApplicationDidBecomeActiveNotification object:nil];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [self.displayLink invalidate];
    self.displayLink = nil;
}

- (void)willEnterBackground:(NSNotification *)notification
{
    [self.displayLink invalidate];
    self.displayLink = nil;
}

- (void)willEnterForeground:(NSNotification *)notification
{
    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
    [self.displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
}

#pragma mark - Setup

- (void)setupProgram
{
    self.blurProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBlurVertexShaderString fragmentShaderString:kFluidBlurFragmentShaderString];
    self.defaultProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidCopyFragmentShaderString];
    self.clearProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidClearFragmentShaderString];
    self.colorProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidColorFragmentShaderString];
    self.checkerboardProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidCheckerBoardFragmentShaderString];
    self.bloomPrefilterProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidBloomPrefilterFragmentShaderString];
    self.bloomBlurProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidBloomBlurFragmentShaderString];
    self.bloomFinalProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidBloomFinalFragmentShaderString];
    self.sunraysMaskProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidSunraysMaskFragmentShaderString];
    self.sunraysProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidSunraysFragmentShaderString];
    self.splatProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidSplatFragmentShaderString];
    self.advectionProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidAdvectionFragmentShaderString];
    self.curlProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidCurlFragmentShaderString];
    self.vorticityProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidVorticityFragmentShaderString];
    self.pressureProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidPressureFragmentShaderString];
    self.gradienSubtractProgram = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidGradientSubtractFragmentShaderString];
    self.displayMaterial = [[FluidProgram alloc] initWithVertexShaderString:kFluidBaseVertexShaderString fragmentShaderString:kFluidDisplayFragmentShaderString];
}

- (void)updateKeywords
{
    if (!self.extension.supportLinearFiltering) {
        [self.advectionProgram setKeywords:@[@"MANUAL_FILTERING"]];
    }
    NSMutableArray *displayKeywords = [NSMutableArray array];
    if (self.config.SHADING) {
        [displayKeywords addObject:@"SHADING"];
    }
    if (self.config.BLOOM) {
        [displayKeywords addObject:@"BLOOM"];
    }
    if (self.config.SUNRAYS) {
        [displayKeywords addObject:@"SUNRAYS"];
    }
    [self.displayMaterial setKeywords:displayKeywords];
}

- (void)setupFramebuffers
{
    CGSize simRes = [self sizeWithResolution:self.config.SIM_RESOLUTION];
    CGSize dyeRes = [self sizeWithResolution:self.config.DYE_RESOLUTION];
    
    GLenum texType = self.extension.halfFloatTexType;
    FluidFormat rgba = self.extension.formatRGBA;
    FluidFormat rg = self.extension.formatRG;
    FluidFormat r = self.extension.formatR;
    GLenum filtering = self.extension.supportLinearFiltering ? GL_LINEAR : GL_NEAREST;
    self.displayBuffer = [[FluidFrameBuffer alloc] initWithWidth:self.canvasWidth height:self.canvasHeight internalFormat:rgba.internalFormat format:rgba.format type:texType param:filtering];
    if (self.dye == nil) {
        self.dye = [[FluidDoubleFrameBuffer alloc] initWithWidth:dyeRes.width height:dyeRes.height internalFormat:rgba.internalFormat format:rgba.format type:texType param:filtering];
    } else {
        FluidDoubleFrameBuffer *dye = [[FluidDoubleFrameBuffer alloc] initWithWidth:dyeRes.width height:dyeRes.height internalFormat:rgba.internalFormat format:rgba.format type:texType param:filtering];
        [self.defaultProgram use];
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, self.dye.read.texture);
        glUniform1i([self.defaultProgram uniformIndex:@"uTexture"], 0);
        [self blit:dye.read];
        self.dye = dye;
    }
    if (self.velocity == nil) {
        self.velocity = [[FluidDoubleFrameBuffer alloc] initWithWidth:simRes.width height:simRes.height internalFormat:rg.internalFormat format:rg.format type:texType param:filtering];
    } else {
        FluidDoubleFrameBuffer *velocity = [[FluidDoubleFrameBuffer alloc] initWithWidth:simRes.width height:simRes.height internalFormat:rg.internalFormat format:rg.format type:texType param:filtering];
        [self.defaultProgram use];
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, self.velocity.read.texture);
        glUniform1i([self.defaultProgram uniformIndex:@"uTexture"], 0);
        [self blit:velocity.read];
        self.velocity = velocity;
    }
    self.divergence = [[FluidFrameBuffer alloc] initWithWidth:simRes.width height:simRes.height internalFormat:r.internalFormat format:r.format type:texType param:GL_NEAREST];
    self.curl = [[FluidFrameBuffer alloc] initWithWidth:simRes.width height:simRes.height internalFormat:r.internalFormat format:r.format type:texType param:GL_NEAREST];
    self.pressure = [[FluidDoubleFrameBuffer alloc] initWithWidth:simRes.width height:simRes.height internalFormat:r.internalFormat format:r.format type:texType param:GL_NEAREST];
    [self setupBloomFramebuffers];
    [self setupSunraysFramebuffers];
}

- (void)setupBloomFramebuffers
{
    CGSize res = [self sizeWithResolution:self.config.BLOOM_RESOLUTION];
    GLenum texType = self.extension.halfFloatTexType;
    FluidFormat rgba = self.extension.formatRGBA;
    GLenum filtering = self.extension.supportLinearFiltering ? GL_LINEAR : GL_NEAREST;
    self.bloom = [[FluidFrameBuffer alloc] initWithWidth:res.width height:res.height internalFormat:rgba.internalFormat format:rgba.format type:texType param:filtering];
    [self.bloomFramebuffers removeAllObjects];
    for (NSInteger i = 0; i < self.config.BLOOM_ITERATIONS; i++) {
        int width = ((int)res.width) >> (i + 1);
        int height = ((int)res.height) >> (i + 1);
        if (width < 2 || height < 2) break;
        
        FluidFrameBuffer *fbo = [[FluidFrameBuffer alloc] initWithWidth:width height:height internalFormat:rgba.internalFormat format:rgba.format type:texType param:filtering];
        [self.bloomFramebuffers addObject:fbo];
    }
}

- (void)setupSunraysFramebuffers
{
    CGSize res = [self sizeWithResolution:self.config.SUNRAYS_RESOLUTION];
    GLenum texType = self.extension.halfFloatTexType;
    FluidFormat r = self.extension.formatR;
    GLenum filtering = self.extension.supportLinearFiltering ? GL_LINEAR : GL_NEAREST;
    self.sunrays = [[FluidFrameBuffer alloc] initWithWidth:res.width height:res.height internalFormat:r.internalFormat format:r.format type:texType param:filtering];
    self.sunraysTemp = [[FluidFrameBuffer alloc] initWithWidth:res.width height:res.height internalFormat:r.internalFormat format:r.format type:texType param:filtering];
}

- (void)multipleSplats:(NSInteger)amount
{
    for (int i = 0; i < amount; i++) {
        GLKVector3 color = [self generateColor];
        color.r *= 10.0;
        color.g *= 10.0;
        color.b *= 10.0;
        float x = (arc4random() % 101) / 100.0;
        float y = (arc4random() % 101) / 100.0;
        float dx = 1000 * ((arc4random() % 101) / 100.0 - 0.5);
        float dy = 1000 * ((arc4random() % 101) / 100.0 - 0.5);
        [self splat:x y:y dx:dx dy:dy color:color];
    }
}

- (void)splatPointer:(FluidPointer *)pointer
{
    float dx = pointer.deltaX * self.config.SPLAT_FORCE;
    float dy = pointer.deltaY * self.config.SPLAT_FORCE;
    [self splat:pointer.texcoordX y:pointer.texcoordY dx:dx dy:dy color:pointer.color];
}

- (void)splat:(float)x y:(float)y dx:(float)dx dy:(float)dy color:(GLKVector3)color
{
    float aspectRatio = 1.0 * self.canvasWidth / self.canvasHeight;
    float radius = self.config.SPLAT_RADIUS / 1000.0 * MAX(1.0, aspectRatio);
    
    [self.splatProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.velocity.read.texture);
    glUniform1i([self.splatProgram uniformIndex:@"uTarget"], 0);
    glUniform1f([self.splatProgram uniformIndex:@"aspectRatio"], aspectRatio);
    glUniform2f([self.splatProgram uniformIndex:@"point"], x, y);
    glUniform3f([self.splatProgram uniformIndex:@"color"], 0.0, 0.0, 0.0);
    glUniform1f([self.splatProgram uniformIndex:@"radius"], radius);
    [self blit:self.velocity.write];
    [self.velocity swap];
    
    [self.splatProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.dye.read.texture);
    glUniform1i([self.splatProgram uniformIndex:@"uTarget"], 0);
    glUniform1f([self.splatProgram uniformIndex:@"aspectRatio"], aspectRatio);
    glUniform2f([self.splatProgram uniformIndex:@"point"], x, y);
    glUniform3f([self.splatProgram uniformIndex:@"color"], color.r, color.g, color.b);
    glUniform1f([self.splatProgram uniformIndex:@"radius"], radius);
    [self blit:self.dye.write];
    [self.dye swap];
}

- (CGSize)sizeWithResolution:(float)resolution
{
    float aspectRatio = 1.0 * self.canvasWidth / self.canvasHeight;
    if (aspectRatio < 1.0) {
        aspectRatio = 1.0 / aspectRatio;
    }
    float min = round(resolution);
    float max = round(resolution * aspectRatio);
    if (self.canvasWidth <= self.canvasHeight) {
        return CGSizeMake(min, max);
    }
    return CGSizeMake(max, min);
}

- (GLKVector3)generateColor
{
    float h = (arc4random() % 101) / 100.0;
    float s = 1.0;
    float v = 1.0;
    
    int i, f, p, q, t;
    i = floor(h * 6);
    f = h * 6 - i;
    p = v * (1 - s);
    q = v * (1 - f * s);
    t = v * (1 - (1 - f) * s);
    
    float r = 0.0, g = 0.0, b = 0.0;
    switch (i % 6) {
        case 0: {
            r = v; g = t; b = p;
            break;
        }
        case 1: {
            r = q; g = v; b = p;
            break;
        }
        case 2: {
            r = p; g = v; b = t;
            break;
        }
        case 3: {
            r = p; g = q; b = v;
            break;
        }
        case 4: {
            r = t; g = p; b = v;
            break;
        }
        case 5: {
            r = v; g = p; b = q;
            break;
        }
    }
    return GLKVector3Make(r * 0.15, g * 0.15, b * 0.15);
}

#pragma mark - Update

- (void)update
{
    CFTimeInterval now = CACurrentMediaTime();
    CFTimeInterval dt = now - self.lastUpdateTime;
    dt = MIN(dt, 0.016666);
    self.lastUpdateTime = now;
    [self updateColors:dt];
    [self applyInputs];
    if (!self.config.PAUSED) {
        [self step:dt];
    }
    [self render:self.displayBuffer];
    [self.glkView display];
}

- (void)updateColors:(double)dt
{
    if (!self.config.COLORFUL) {
        return;
    }
    
    self.colorUpdateTimer += dt * self.config.COLOR_UPDATE_SPEED;
    if (self.colorUpdateTimer >= 1.0) {
        self.colorUpdateTimer = self.colorUpdateTimer - (int)self.colorUpdateTimer;
        for (FluidPointer *pointer in self.pointers) {
            pointer.color = [self generateColor];
        }
    }
}

- (void)applyInputs
{
    NSArray *splatStack = [self.splatStack copy];
    for (NSInteger i = 0; i < splatStack.count; i++) {
        int amount = [[splatStack objectAtIndex:i] intValue];
        [self.splatStack removeObjectAtIndex:i];
        [self multipleSplats:amount];
    }
    
    for (FluidPointer *pointer in self.pointers) {
        if (pointer.moved) {
            pointer.moved = NO;
            [self splatPointer:pointer];
        }
    }
}

- (void)step:(double)dt
{
    glDisable(GL_BLEND);
    
    [self.curlProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.velocity.read.texture);
    glUniform1i([self.curlProgram uniformIndex:@"uVelocity"], 0);
    glUniform2f([self.curlProgram uniformIndex:@"texelSize"], self.velocity.texelSizeX, self.velocity.texelSizeY);
    [self blit:self.curl];
    
    [self.vorticityProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.velocity.read.texture);
    glUniform1i([self.vorticityProgram uniformIndex:@"uVelocity"], 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, self.curl.texture);
    glUniform1i([self.vorticityProgram uniformIndex:@"uCurl"], 1);
    glUniform1f([self.vorticityProgram uniformIndex:@"curl"], self.config.CURL);
    glUniform1f([self.vorticityProgram uniformIndex:@"dt"], dt);
    glUniform2f([self.vorticityProgram uniformIndex:@"texelSize"], self.velocity.texelSizeX, self.velocity.texelSizeY);
    [self blit:self.velocity.write];
    [self.velocity swap];
    
    [self.divergenceProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.velocity.read.texture);
    glUniform1i([self.divergenceProgram uniformIndex:@"uVelocity"], 0);
    glUniform2f([self.divergenceProgram uniformIndex:@"texelSize"], self.velocity.texelSizeX, self.velocity.texelSizeY);
    [self blit:self.divergence];
    
    [self.clearProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.pressure.read.texture);
    glUniform1i([self.clearProgram uniformIndex:@"uTexture"], 0);
    glUniform1f([self.clearProgram uniformIndex:@"value"], self.config.PRESSURE);
    [self blit:self.pressure.write];
    [self.pressure swap];
    
    [self.pressureProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.divergence.texture);
    glUniform1i([self.pressureProgram uniformIndex:@"uDivergence"], 0);
    for (int i = 0; i < self.config.PRESSURE_ITERATIONS; i++) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, self.pressure.read.texture);
        glUniform1i([self.pressureProgram uniformIndex:@"uPressure"], 1);
        [self blit:self.pressure.write];
        [self.pressure swap];
    }
    
    [self.gradienSubtractProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.pressure.read.texture);
    glUniform1i([self.gradienSubtractProgram uniformIndex:@"uPressure"], 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, self.velocity.read.texture);
    glUniform1i([self.gradienSubtractProgram uniformIndex:@"uVelocity"], 1);
    glUniform2f([self.gradienSubtractProgram uniformIndex:@"texelSize"], self.velocity.texelSizeX, self.velocity.texelSizeY);
    [self blit:self.velocity.write];
    [self.velocity swap];
    
    [self.advectionProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.velocity.read.texture);
    glUniform1i([self.advectionProgram uniformIndex:@"uVelocity"], 0);
    glUniform1i([self.advectionProgram uniformIndex:@"uSource"], 0);
    glUniform1f([self.advectionProgram uniformIndex:@"dt"], dt);
    glUniform1f([self.advectionProgram uniformIndex:@"dissipation"], self.config.VELOCITY_DISSIPATION);
    glUniform2f([self.advectionProgram uniformIndex:@"texelSize"], self.velocity.texelSizeX, self.velocity.texelSizeY);
    if (!self.extension.supportLinearFiltering) {
        glUniform2f([self.advectionProgram uniformIndex:@"dyeTexelSize"], self.velocity.texelSizeX, self.velocity.texelSizeY);
    }
    [self blit:self.velocity.write];
    [self.velocity swap];
    
    [self.advectionProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.velocity.read.texture);
    glUniform1i([self.advectionProgram uniformIndex:@"uVelocity"], 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, self.dye.read.texture);
    glUniform1i([self.advectionProgram uniformIndex:@"uSource"], 1);
    glUniform1f([self.advectionProgram uniformIndex:@"dt"], dt);
    glUniform1f([self.advectionProgram uniformIndex:@"dissipation"], self.config.DENSITY_DISSIPATION);
    glUniform2f([self.advectionProgram uniformIndex:@"texelSize"], self.dye.texelSizeX, self.dye.texelSizeY);
    if (!self.extension.supportLinearFiltering) {
        glUniform2f([self.advectionProgram uniformIndex:@"dyeTexelSize"], self.dye.texelSizeX, self.dye.texelSizeY);
    }
    [self blit:self.dye.write];
    [self.dye swap];
}

- (void)blit:(FluidFrameBuffer *)target
{
    [self blit:target clear:NO];
}

- (void)blit:(FluidFrameBuffer *)target clear:(BOOL)clear
{
    static GLfloat kVertices[] = {
        -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
    };
    
    glBindFramebuffer(GL_FRAMEBUFFER, target.fbo);
    glViewport(0, 0, target.width, target.height);
    if (clear) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, kVertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

#pragma mark - Render

- (void)render:(FluidFrameBuffer *)target
{
    if (self.config.BLOOM) {
        [self applyBloom:self.dye.read destination:self.bloom];
    }
    if (self.config.SUNRAYS) {
        [self applySunrays:self.dye.read mask:self.dye.write destination:self.sunrays];
        [self applyBlur:self.sunrays temp:self.sunraysTemp iterations:1];
    }
    if (target == nil || !self.config.TRANSPARENT) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glDisable(GL_BLEND);
    }
    if (!self.config.TRANSPARENT) {
        [self.colorProgram use];
        glUniform4f([self.colorProgram uniformIndex:@"color"], self.config.BACK_COLOR.r, self.config.BACK_COLOR.g, self.config.BACK_COLOR.b, 1.0);
        [self blit:target];
    }
    if (target == nil && self.config.TRANSPARENT) {
        [self.checkerboardProgram use];
        glUniform1f([self.checkerboardProgram uniformIndex:@"aspectRatio"], 1.0 * target.width / target.height);
        [self blit:target];
    }
    [self drawDispaly:target];
}

- (void)drawDispaly:(FluidFrameBuffer *)target
{
    [self.displayMaterial use];
    if (self.config.SHADING) {
        glUniform2f([self.displayMaterial uniformIndex:@"texelSize"], 1.0 / target.width, 1.0 / target.height);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.dye.read.texture);
    glUniform1i([self.displayMaterial uniformIndex:@"uTexture"], 0);
    if (self.config.BLOOM) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, self.bloom.texture);
        glUniform1i([self.displayMaterial uniformIndex:@"uBloom"], 1);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, self.ditheringTexture.name);
        glUniform1i([self.displayMaterial uniformIndex:@"uDithering"], 2);
        glUniform2f([self.displayMaterial uniformIndex:@"ditherScale"], 1.0 * target.width / self.ditheringTexture.width, 1.0 * target.height / self.ditheringTexture.height);
    }
    if (self.config.SUNRAYS) {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, self.sunrays.texture);
        glUniform1i([self.displayMaterial uniformIndex:@"uSunrays"], 3);
    }
    [self blit:target];
}

- (void)applyBloom:(FluidFrameBuffer *)source destination:(FluidFrameBuffer *)destination
{
    if (self.bloomFramebuffers.count < 2) {
        return;
    }
    
    FluidFrameBuffer *last = destination;
    
    glDisable(GL_BLEND);
    [self.bloomPrefilterProgram use];
    float knee = self.config.BLOOM_THRESHOLD * self.config.BLOOM_SOFT_KNEE + 0.0001;
    float curve0 = self.config.BLOOM_THRESHOLD - knee;
    float curve1 = knee * 2;
    float curve2 = 0.25 / knee;
    glUniform3f([self.bloomPrefilterProgram uniformIndex:@"curve"], curve0, curve1, curve2);
    glUniform1f([self.bloomPrefilterProgram uniformIndex:@"threshold"], self.config.BLOOM_THRESHOLD);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, source.texture);
    glUniform1i([self.bloomPrefilterProgram uniformIndex:@"uTexture"], 0);
    [self blit:last];
    
    [self.bloomBlurProgram use];
    for (NSInteger i = 0; i < self.bloomFramebuffers.count; i++) {
        FluidFrameBuffer *dest = self.bloomFramebuffers[i];
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, last.texture);
        glUniform1i([self.bloomBlurProgram uniformIndex:@"uTexture"], 0);
        glUniform2f([self.bloomBlurProgram uniformIndex:@"texelSize"], last.texelSizeX, last.texelSizeY);
        [self blit:dest];
        last = dest;
    }
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    for (NSInteger i = self.bloomFramebuffers.count - 2; i >= 0; i--) {
        FluidFrameBuffer *baseTex = self.bloomFramebuffers[i];
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, last.texture);
        glUniform1i([self.bloomBlurProgram uniformIndex:@"uTexture"], 0);
        glUniform2f([self.bloomBlurProgram uniformIndex:@"texelSize"], last.texelSizeX, last.texelSizeY);
        [self blit:baseTex];
        last = baseTex;
    }
    
    glDisable(GL_BLEND);
    [self.bloomFinalProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, last.texture);
    glUniform1i([self.bloomFinalProgram uniformIndex:@"uTexture"], 0);
    glUniform2f([self.bloomFinalProgram uniformIndex:@"texelSize"], last.texelSizeX, last.texelSizeY);
    glUniform1f([self.bloomFinalProgram uniformIndex:@"intensity"], self.config.BLOOM_INTENSITY);
    [self blit:destination];
}

- (void)applySunrays:(FluidFrameBuffer *)source mask:(FluidFrameBuffer *)mask destination:(FluidFrameBuffer *)destination
{
    glDisable(GL_BLEND);
    [self.sunraysMaskProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, source.texture);
    glUniform1i([self.sunraysMaskProgram uniformIndex:@"uTexture"], 0);
    [self blit:mask];
    
    [self.sunraysProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mask.texture);
    glUniform1i([self.sunraysProgram uniformIndex:@"uTexture"], 0);
    glUniform1f([self.sunraysProgram uniformIndex:@"weight"], self.config.SUNRAYS_WEIGHT);
    [self blit:destination];
}

- (void)applyBlur:(FluidFrameBuffer *)target temp:(FluidFrameBuffer *)temp iterations:(int)iterations
{
    [self.blurProgram use];
    for (int i = 0; i < iterations; i++) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, target.texture);
        glUniform1i([self.blurProgram uniformIndex:@"uTexture"], 0);
        glUniform2f([self.blurProgram uniformIndex:@"texelSize"], target.texelSizeX, 0.0);
        [self blit:temp];
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, temp.texture);
        glUniform1i([self.blurProgram uniformIndex:@"uTexture"], 0);
        glUniform2f([self.blurProgram uniformIndex:@"texelSize"], 0.0, target.texelSizeY);
        [self blit:target];
    }
}

#pragma mark - UITouch

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [super touchesBegan:touches withEvent:event];
    
    FluidPointer *pointer = [self.pointers firstObject];
    CGPoint point = [[touches anyObject] locationInView:self.view];
    if (!CGRectContainsPoint(self.glkView.frame, point)) {
        pointer.down = NO;
        pointer.moved = NO;
        return;
    }
    
    // update
    float posX = point.x - CGRectGetMinX(self.glkView.frame);
    float posY = point.y - CGRectGetMinY(self.glkView.frame);
    pointer.down = YES;
    pointer.moved = NO;
    pointer.texcoordX = posX / CGRectGetWidth(self.glkView.frame);
    pointer.texcoordY = 1.0 - posY / CGRectGetHeight(self.glkView.frame);
    pointer.prevTexcoordX = pointer.texcoordX;
    pointer.prevTexcoordY = pointer.texcoordY;
    pointer.deltaX = 0;
    pointer.deltaY = 0;
    pointer.color = [self generateColor];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [super touchesBegan:touches withEvent:event];
    
    FluidPointer *pointer = [self.pointers firstObject];
    CGPoint point = [[touches anyObject] locationInView:self.view];
    if (!CGRectContainsPoint(self.glkView.frame, point)) {
        pointer.down = NO;
        pointer.moved = NO;
        return;
    }
    
    // update
    float posX = point.x - CGRectGetMinX(self.glkView.frame);
    float posY = point.y - CGRectGetMinY(self.glkView.frame);
    float aspectRatio = CGRectGetWidth(self.glkView.frame) / CGRectGetHeight(self.glkView.frame);
    pointer.down = YES;
    pointer.moved = YES;
    pointer.prevTexcoordX = pointer.texcoordX;
    pointer.prevTexcoordY = pointer.texcoordY;
    pointer.texcoordX = posX / CGRectGetWidth(self.glkView.frame);
    pointer.texcoordY = 1.0 - posY / CGRectGetHeight(self.glkView.frame);
    if (aspectRatio < 1.0) {
        pointer.deltaX = (pointer.texcoordX - pointer.prevTexcoordX) * aspectRatio;
        pointer.deltaY = pointer.texcoordY - pointer.prevTexcoordY;
    } else {
        pointer.deltaX = pointer.texcoordX - pointer.prevTexcoordX;
        pointer.deltaY = (pointer.texcoordY - pointer.prevTexcoordY) / aspectRatio;
    }
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [super touchesBegan:touches withEvent:event];
    FluidPointer *pointer = [self.pointers firstObject];
    pointer.down = NO;
    pointer.moved = NO;
}

#pragma mark - GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    static GLfloat kDisplayVertices[] = {
        -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
    };
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    [self.defaultProgram use];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self.displayBuffer.texture);
    glUniform1f([self.defaultProgram uniformIndex:@"uTexture"], 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, kDisplayVertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
