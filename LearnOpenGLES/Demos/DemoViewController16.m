//
//  DemoViewController16.m
//  LearnOpenGLES
//
//  Created by apple on 2019/7/29.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoViewController16.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "GLProgram.h"
#import "DemoUtils.h"

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

static NSString * kDemoViewController16CellResueID = @"kDemoViewController16CellResueID";

@interface DemoViewController16Cell : UICollectionViewCell

@property (nonatomic, strong) UILabel *titleLabel;

@end

@implementation DemoViewController16Cell

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.titleLabel = [[UILabel alloc] initWithFrame:self.bounds];
        self.titleLabel.backgroundColor = [UIColor colorWithRed:0.9 green:0.9 blue:0.9 alpha:1.0];
        self.titleLabel.textAlignment = NSTextAlignmentCenter;
        self.titleLabel.textColor = [UIColor orangeColor];
        [self.contentView addSubview:self.titleLabel];
    }
    return self;
}

@end

@interface DemoViewController16 () <UICollectionViewDataSource, UICollectionViewDelegate>
{
    GLint _filterPositionAttribute, _filterTextureCoordinateAttribute;
    GLint _filterInputTextureUniform, _filterInputTimeUniform, _filterInputTextureSizeUniform;
    
    GLint _drawableWidth, _drawableHeight;
    GLuint _defaultFrameBuffer, _colorRenderBuffer, _depthRenderBuffer;
    GLuint _textureID;
}

@property (nonatomic, strong) UICollectionView *collectionView;
@property (nonatomic, strong) EAGLContext *eglContext;
@property (nonatomic, strong) CAEAGLLayer *eglLayer;
// 着色器
@property (nonatomic, strong) GLProgram *program;
// 用于刷新屏幕
@property (nonatomic, strong) CADisplayLink *displayLink;
// 开始的时间戳
@property (nonatomic, assign) NSTimeInterval startTimestamp;
@property (nonatomic, assign) NSTimeInterval lastTimestamp;
// 滤镜组
@property (nonatomic, copy) NSArray *dataArray;
@property (nonatomic, copy) NSArray *filterArray;

@end

@implementation DemoViewController16

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.view.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    
    UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
    layout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
    layout.itemSize = CGSizeMake(72, 40);
    layout.minimumLineSpacing = 10;
    layout.minimumInteritemSpacing = 0;
    self.collectionView = [[UICollectionView alloc] initWithFrame:CGRectMake(0, CGRectGetHeight(self.view.bounds) - 120, CGRectGetWidth(self.view.bounds), 40) collectionViewLayout:layout];
    self.collectionView.backgroundColor = [UIColor clearColor];
    self.collectionView.contentInset = UIEdgeInsetsMake(0, 10, 0, 10);
    self.collectionView.showsVerticalScrollIndicator = NO;
    self.collectionView.showsHorizontalScrollIndicator = NO;
    self.collectionView.dataSource = self;
    self.collectionView.delegate = self;
    [self.collectionView registerClass:[DemoViewController16Cell class] forCellWithReuseIdentifier:kDemoViewController16CellResueID];
    [self.view addSubview:self.collectionView];
    
    // 1.创建opengl上下文
    self.eglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    [EAGLContext setCurrentContext:self.eglContext];
    
    // 2.创建layer，用于显示
    self.eglLayer = [CAEAGLLayer layer];
    self.eglLayer.frame = CGRectMake(0, (CGRectGetHeight(self.view.bounds) - CGRectGetWidth(self.view.bounds)) * 0.5, CGRectGetWidth(self.view.bounds), CGRectGetWidth(self.view.bounds));
    self.eglLayer.contentsScale = [UIScreen mainScreen].scale;
    self.eglLayer.drawableProperties = @
    {
        kEAGLDrawablePropertyRetainedBacking : @(NO),
        kEAGLDrawablePropertyColorFormat : kEAGLColorFormatRGBA8,
    };
    [self.view.layer addSublayer:self.eglLayer];
    [self setupFrameBuffer];
    
    // 3.创建纹理
    NSString *imagePath = [[NSBundle mainBundle] pathForResource:@"meimei" ofType:@"jpg"];
    UIImage *textureImage = [UIImage imageWithContentsOfFile:imagePath];
    _textureID = [DemoUtils createTextureFromImage:textureImage.CGImage flippedX:NO flippedY:YES];
    
    // 4.配置着色器
    self.dataArray = @[@"无", @"灰度", @"颠倒", @"旋涡", @"马赛克", @"马赛克2", @"马赛克3",  @"缩放", @"灵魂出窍", @"抖动", @"闪白", @"毛刺", @"眩晕", @"电击", @"动感光波", @"暗黑幻境", @"视频分裂", @"百叶窗", @"幻影", @"镜像"];
    self.filterArray = @[@"Normal", @"Gray", @"Reversal", @"Cirlce", @"Mosaic", @"HexagonMosaic", @"TriangularMosaic", @"Scale", @"SoulOut", @"Shake", @"ShineWhite", @"Glitch", @"Vertigo", @"Electric", @"RockLight", @"DarkDream", @"SoulSplit", @"LinearShadow", @"Phantom", @"Mirror"];
    [self setupFilerProgram:self.filterArray.firstObject];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [self stopFilerAnimation];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self startFilerAnimation];
}

#pragma mark - UICollectionViewDataSource

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    return self.dataArray.count;
}

// The cell that is returned must be retrieved from a call to -dequeueReusableCellWithReuseIdentifier:forIndexPath:
- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    DemoViewController16Cell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:kDemoViewController16CellResueID forIndexPath:indexPath];
    if (indexPath.item < self.dataArray.count) {
        cell.titleLabel.text = [self.dataArray objectAtIndex:indexPath.item];
    }
    return cell;
}

#pragma mark - UICollectionViewDelegate

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
    [collectionView deselectItemAtIndexPath:indexPath animated:NO];
    
    [self stopFilerAnimation];
    [self setupFilerProgram:self.filterArray[indexPath.item]];
    [self startFilerAnimation];
}

// 停止动画
- (void)stopFilerAnimation
{
    if (self.displayLink) {
        [self.displayLink invalidate];
        self.displayLink = nil;
    }
    self.startTimestamp = 0;
    self.lastTimestamp = 0;
}

// 开始一个滤镜动画
- (void)startFilerAnimation
{
    [self stopFilerAnimation];
    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
    [self.displayLink addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSRunLoopCommonModes];
}

// 创建着色器
- (void)setupFilerProgram:(NSString *)shaderName
{
    NSBundle *effectBundle = [NSBundle bundleWithPath:[[NSBundle mainBundle] pathForResource:@"Effect" ofType:@"bundle"]];
    NSString *vertexShaderPath = [effectBundle pathForResource:shaderName ofType:@"vsh" inDirectory:shaderName];
    NSString *fragmentShaderPath = [effectBundle pathForResource:shaderName ofType:@"fsh" inDirectory:shaderName];
    self.program = [[GLProgram alloc] initWithVertexShaderString:[NSString stringWithContentsOfFile:vertexShaderPath encoding:NSUTF8StringEncoding error:nil] fragmentShaderString:[NSString stringWithContentsOfFile:fragmentShaderPath encoding:NSUTF8StringEncoding error:nil]];
    [self.program addAttribute:@"position"];
    [self.program addAttribute:@"inputTextureCoordinate"];
    [self.program link];
    
    _filterPositionAttribute = [self.program attributeIndex:@"position"];
    _filterTextureCoordinateAttribute = [self.program attributeIndex:@"inputTextureCoordinate"];
    _filterInputTextureUniform = [self.program uniformIndex:@"inputImageTexture"];
    _filterInputTextureSizeUniform = [self.program uniformIndex:@"inputTextureSize"];
    _filterInputTimeUniform = [self.program uniformIndex:@"inputTime"];
}

// FBO
- (void)setupFrameBuffer
{
    _defaultFrameBuffer = 0;
    _colorRenderBuffer = 0;
    _depthRenderBuffer = 0;
    _drawableWidth = 0;
    _drawableHeight = 0;
    
    // FBO
    glGenFramebuffers(1, &_defaultFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _defaultFrameBuffer);
    
    // 创建颜色缓冲
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    // iOS下使用renderbufferStorage:fromDrawable:函数分配空间
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, _drawableWidth, _drawableHeight);
    [self.eglContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:self.eglLayer];
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    // 获取画布宽高
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &_drawableWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &_drawableHeight);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    // 创建深度缓冲
    GLenum internalformat = GL_DEPTH24_STENCIL8_OES;
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    /**
     * target: 指定renderbuffer目标，符号常量必须为GL_RENDERBUFFER。
     * internalformat: 指定渲染缓冲区的颜色可渲染，深度可渲染或模板可渲染格式，
     *   深度格式GLES2默认只有GL_DEPTH_COMPONENT16，但是可以使用扩展GL_DEPTH_COMPONENT24_OES
     *   如果使用模板，设置为GL_DEPTH24_STENCIL8_OES，即24位深度，8位模板
     * width: 指定渲染缓冲区的宽度（以像素为单位）。
     * height: 指定渲染缓冲区的高度（以像素为单位）。
     */
    glRenderbufferStorage(GL_RENDERBUFFER, internalformat, _drawableWidth, _drawableHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
    // 附加模板缓冲，可以与深度缓冲共用一个depthRenderBuffer，前提是internalformat设置为GL_DEPTH24_STENCIL8_OES
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

- (void)bindDrawable
{
    glBindFramebuffer(GL_FRAMEBUFFER, _defaultFrameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    glViewport(0, 0, _drawableWidth, _drawableHeight);
}

// 更新
- (void)update
{
    if (self.startTimestamp <= 0) {
        self.startTimestamp = self.displayLink.timestamp;
        self.lastTimestamp = self.startTimestamp;
    }
    // 更新模型变换
    // 控制绘制频率
    NSTimeInterval interval = self.displayLink.timestamp - self.lastTimestamp;
    if (interval * 1000 < 50) {
        return;
    }
    self.lastTimestamp = self.displayLink.timestamp;
    [self bindDrawable];
    [self drawRect:self.eglLayer.bounds];
    [self.eglContext presentRenderbuffer:GL_RENDERBUFFER];
}

// 绘制
- (void)drawRect:(CGRect)rect
{
    // 清除画布
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 启用着色器
    [self.program use];
    
    // 传入时间
    CGFloat inputTime = self.displayLink.timestamp - self.startTimestamp;
    glUniform1f(_filterInputTimeUniform, inputTime);
    
    // 传入宽高
    GLfloat sizeArray[2];
    sizeArray[0] = _drawableWidth;
    sizeArray[1] = _drawableHeight;
    glUniform2fv(_filterInputTextureSizeUniform, 1, sizeArray);
    
    // 绑定纹理
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glUniform1i(_filterInputTextureUniform, 0);
    
    // 启用属性
    glEnableVertexAttribArray(_filterPositionAttribute);
    glEnableVertexAttribArray(_filterTextureCoordinateAttribute);
    
    // 赋值顶点
    glVertexAttribPointer(_filterPositionAttribute, 3, GL_FLOAT, 0, 0, imageVertices);
    glVertexAttribPointer(_filterTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates);
    // 绘制
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glDisableVertexAttribArray(_filterPositionAttribute);
    glDisableVertexAttribArray(_filterTextureCoordinateAttribute);
}

- (void)dealloc
{
    if ([EAGLContext currentContext] != self.eglContext)
    {
        [EAGLContext setCurrentContext:self.eglContext];
        [self.eglContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:nil];
    }
    if (_defaultFrameBuffer != 0)
    {
        glDeleteFramebuffers(1, &_defaultFrameBuffer);
        _defaultFrameBuffer = 0;
    }
    
    if (_colorRenderBuffer != 0)
    {
        glDeleteRenderbuffers(1, &_colorRenderBuffer);
        _colorRenderBuffer = 0;
    }
    
    if (_depthRenderBuffer != 0)
    {
        glDeleteRenderbuffers(1, &_depthRenderBuffer);
        _depthRenderBuffer = 0;
    }
    if (_textureID)
    {
        glDeleteTextures(1, &_textureID);
        _textureID = 0;
    }
    [EAGLContext setCurrentContext:nil];
    self.eglContext = nil;
}

@end
