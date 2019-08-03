//
//  DemoViewController5.m
//  LearnOpenGLES
//
//  Created by apple on 2018/10/26.
//  Copyright © 2018 erpapa. All rights reserved.
//

#import "DemoViewController5.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

typedef struct {
    GLfloat Positon[3];  // 位置
    GLfloat Normal[3];   // 法线
    GLfloat Color[4];    // 颜色
    GLfloat TexCoord[2]; // 纹理
} Vertex;

// 顶点坐标既法线和纹理
// z取值[-1~1.0]，屏幕上方为正，宽度小于当前view宽度，如果为0，则显示的宽度为当前view的宽度
// 在 GL_TRIANGLE_STRIP 状态下是: 0、1、2 ; 2、1、3 ; 2、3、4 ; 4、3、5 这4个三角形。
// 在 GL_TRIANGLE_FAN 状态下是: 0、1、2 ; 0、2、3 ; 0、3、4 ; 0、4、5 这4个三角形。// 扇形
static Vertex GL_TRIANGLES_VertexData[] = {
    
    0.5f, -0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   1.0f, 0.0f,// 0 右下
    -0.5f, 0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   0.0f, 1.0f,// 1 左上
    -0.5f, -0.5f, -0.9f,    1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,// 2 左下
    -0.5f, 0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   0.0f, 1.0f,// 3 左上
    0.5f, 0.5f, -0.9f,      1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,// 4 右上
    0.5f, -0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   1.0f, 0.0f,// 5 右下
};

// 在 GL_TRIANGLE_STRIP 状态下是: 0、1、2 ; 2、1、3 这2个三角形。
static Vertex GL_RIANGLE_STRIP_VertexData[] = {
    
    -0.5f, -0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,// 0 左下
    -0.5f, 0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   0.0f, 1.0f,// 1 左上
    0.5f, -0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   1.0f, 0.0f,// 2 右下
    0.5f, 0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,// 3 右上
    
};

// 在 GL_TRIANGLE_FAN   状态下是: 0、1、2 ; 0、2、3 这2个三角形。
static Vertex GL_TRIANGLE_FAN_VertexData[] = {
    
    0.5f, -0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   1.0f, 0.0f,// 0 右下
    -0.5f, -0.5f, -0.9f,    1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,// 1 左下
    -0.5f, 0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   0.0f, 1.0f,// 2 左上
    0.5f, 0.5f, -0.9f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,// 3 右上
};

static GLubyte GL_ELEMENT_Indices[] = {
    0, 1, 2,
    2, 1, 3
};


//每行顶点数据的排列含义是：
//
//顶点X、顶点Y，顶点Z、法线X、法线Y、法线Z、纹理S、纹理T。
//
//在后面解析此数组时，将参考此规则。
//
//顶点位置用于确定在什么地方显示，法线用于光照模型计算，纹理则用在贴图中。
//
//一般约定为“顶点以逆时针次序出现在屏幕上的面”为“正面”。
//
//世界坐标是OpenGL中用来描述场景的坐标，Z+轴垂直屏幕向外，X+从左到右，Y+轴从下到上，是右手笛卡尔坐标系统。我们用这个坐标系来描述物体及光源的位置。

@interface DemoViewController5 ()
{
    GLuint VAO, VBO, EBO;
}
@property (nonatomic, strong) EAGLContext *context;
@property (nonatomic, strong) GLKBaseEffect *effect;

@end

@implementation DemoViewController5

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    assert(self.context);
    
    GLKView *glkView = (GLKView *)self.view;
    glkView.context = self.context;
    /**
     * 1.OpenGL上下文有一个缓冲区，它用以存储将在屏幕中显示的颜色。你可以使用其属性来设置缓冲区中每个像素的颜色格式。
     * 2.缺省值是GLKViewDrawableColorFormatRGBA8888，即缓冲区的每个像素的最小组成部分(-个像素有四个元素组成 RGBA)使用8个bit(如R使用8个bit)（所以每个像素4个字节 既 4*8 个bit）。这非常好，因为它给了你提供了最广泛的颜色范围，让你的app看起来更好。
     * 3.但是如果你的app允许更小范围的颜色，你可以设置为GLKViewDrawableColorFormatRGB565，从而使你的app消耗更少的资源（内存和处理时间）。
     **/
    glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    /**
     * 1.OpenGL上下文还可以（可选地）有另一个缓冲区，称为深度缓冲区。
     * 2.这帮助我们确保更接近观察者的对象显示在远一些的对象的前面（意思就是离观察者近一些的对象会挡住在它后面的对象）
     *   其缺省的工作方式是：OpenGL把接近观察者的对象的所有像素存储到深度缓冲区，
     *   当开始绘制一个像素时，它（OpenGL）首先检查深度缓冲区，看是否已经绘制了更接近观察者的什么东西，
     *   如果是则忽略它（要绘制的像素，就是说，在绘制一个像素之前，看看前面有没有挡着它的东西，如果有那就不用绘制了）。
     *   否则，把它增加到深度缓冲区和颜色缓冲区。
     * 3.你可以设置这个属性，以选择深度缓冲区的格式。缺省值是GLKViewDrawableDepthFormatNone，意味着完全没有深度缓冲区。
     *   但是如果你要使用这个属性（一般用于3D游戏），你应该选择GLKViewDrawableDepthFormat16或GLKViewDrawableDepthFormat24。
     *   这里的差别是使用GLKViewDrawableDepthFormat16将消耗更少的资源，但是当对象非常接近彼此时，你可能存在渲染问题
     **/
    glkView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    /**
     * 将此“EAGLContext”实例设置为OpenGL的“当前激活”的“Context”
     * 以后所有“GL”的指令均作用在这个“Context”上
     **/
    [EAGLContext setCurrentContext:self.context];
    // 发送第一个“GL”指令：激活“深度检测”
    // 启用GL_DEPTH_TEST，必须先设置drawableDepthFormat
    glEnable(GL_DEPTH_TEST);
    
    // 1.写入过程
    // 首先将数据保存进GUP的一个缓冲区中，然后再按一定规则，将数据取出，复制到各个通用顶点属性中。
    // 注：如果顶点数据只有一种类型（如单纯的位置坐标），换言之，在读数据时，不需要确定第一个数据的内存位置（总是从0开始），则不必事先保存进缓冲区。

    // 2.顶点数组对象
    // 2.1.创建顶点数组对象VAO，一个VAO可以保存一组VBO和一个EBO
    glGenVertexArraysOES(1, &VAO);
    glBindVertexArrayOES(VAO);
    
    // 2.2.创建顶点缓冲对象VBO
    glGenBuffers(1, &VBO); // 让OpenGL自动分配一个缓冲区并且返回这个标识的值
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定这个缓冲区到当前context
    // 预先定义的顶点数据“VertexData”复制进这个缓冲区中
    // 注：参数“GL_STATIC_DRAW”，它表示此缓冲区内容只能被修改一次，但可以无限次读取。
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_RIANGLE_STRIP_VertexData), GL_RIANGLE_STRIP_VertexData, GL_STATIC_DRAW);
    
    // 将缓冲区的数据复制进通用顶点属性中
    // 激活顶点属性（默认它的关闭的）,GLKVertexAttribPosition是顶点属性集中“位置Position”属性的索引。
    // 顶点属性集中包含五种属性：位置、法线、颜色、纹理0，纹理1。它们的索引值是0~4。
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    // 参数含义分别为：顶点属性索引（这里是位置）、3个分量的矢量、类型是浮点（GL_FLOAT）、填充时不需要单位化（GL_FALSE）
    // sizeof(Vertex)==4*12==48（GL_FLOAT占4个字节，每行有12个浮点数，如果数据连续存放，则为0）
    // 最后一个参数是一个偏移量的指针，用来确定“第一个数据”将从内存数据块的什么地方开始
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float *)NULL + 0);
    
    // 法线，3个分量
    glEnableVertexAttribArray(GLKVertexAttribNormal); // 法线
    glVertexAttribPointer(GLKVertexAttribNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float *)NULL + 3);
    
    // 颜色，4个分量
    // 由于使用贴图，所以禁用GLKVertexAttribColor
    // glEnableVertexAttribArray(GLKVertexAttribColor); // 颜色
    // glVertexAttribPointer(GLKVertexAttribColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float *)NULL + 6);
    
    // 纹理，纹理坐标只有S和T，2个分量
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0); // 纹理
    glVertexAttribPointer(GLKVertexAttribTexCoord0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float *)NULL + 10);
    
    // 2.3.创建顶点索引对象EBO，可供glDrawElements使用
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_ELEMENT_Indices), GL_ELEMENT_Indices, GL_STATIC_DRAW);
    
    // glBindBuffer(GL_ARRAY_BUFFER, 0); // 不可以解绑，此时VAO管理着它们
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // 不可以解绑，此时VAO管理着它们
    glBindVertexArrayOES(0); // 解绑VAO（这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法）

    // 4.创建一个GLK内置的“着色效果”
    self.effect = [[GLKBaseEffect alloc] init];
    
    // 4.1.给它提供一个光源
    self.effect.light0.enabled = GL_FALSE; // 不启用光源
    self.effect.light0.position = GLKVector4Make(0.0, 0.0, 0.0, 1.0);
    self.effect.light0.ambientColor = GLKVector4Make(0.0, 0.0, 0.0, 1.0);
    self.effect.light0.diffuseColor = GLKVector4Make(1.0, 1.0, 1.0, 1.0);
    
    // 4.2.将纹理坐标原点改为左下角（GLKit加载纹理，默认都是把坐标设置在“左上角”。然而，OpenGL的纹理贴图坐标却是在左下角，这样刚好颠倒）
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"for_test" ofType:@"jpg"];
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:@(1),GLKTextureLoaderOriginBottomLeft, nil];
    GLKTextureInfo *textureInfo = [GLKTextureLoader textureWithContentsOfFile:filePath options:options error:nil];
    self.effect.texture2d0.enabled = GL_TRUE;
    self.effect.texture2d0.name = textureInfo.name;
}

- (void)update
{
    // 使用透视矩阵
    // 参数1：视角，要求输入幅度，GLKMathDegreesToRadians帮助我们把角度值转换为幅度
    // 参数2：宽高比
    // 参数3：near，
    // 参数4：far
    // near和far共同决定了可视深度，都必须为正值，near一般设为一个比较小的数，far必须大于near。
    CGSize size = self.view.bounds.size;
    GLKMatrix4 projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(65.0), size.width / size.height, 0.1f, 10.0f);
    self.effect.transform.projectionMatrix = projectionMatrix;
    
    // 上图看起来感觉像一个正方形，但似乎左右两边没显示完整。原因是，正方形与透视视点距离太近。
    // 有两个方法解决这个问题：一是修改原始的顶点数据（Z轴值），使之透视视点；二是通过所谓的“模型视图矩阵”，将正方形“变换”到远一点的位置。
    GLKMatrix4 modelMatrix = GLKMatrix4MakeTranslation(0.0, 0.0, -1.0); // 模型平移
    GLKMatrix4 viewMatrix = GLKMatrix4MakeLookAt(0.0, 0.0, 1.0, 0, 0, -1.0, 0, 1, 0); // 指定摄像机位置
    self.effect.transform.modelviewMatrix = GLKMatrix4Multiply(viewMatrix, modelMatrix);
}

#pragma mark - GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    // 渲染前的“清除”操作，清除颜色缓冲区和深度缓冲区中的内容，并且填充淡蓝色背景（默认背景是黑色）。
    // GL_COLOR_BUFFER_BIT: 当前可写的颜色缓冲
    // GL_DEPTH_BUFFER_BIT: 深度缓冲
    // GL_ACCUM_BUFFER_BIT: 累积缓冲
    // GL_STENCIL_BUFFER_BIT: 模板缓冲
    glClearColor(0.3f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 让OpenGL“画出”两个三角形（拼合为一个正方形）。OpenGL会自动从通用顶点属性中取出这些数据、组装、再用“Effect”内置的着色器渲染。
    // 让“效果Effect”针对当前“Context”的状态进行一些配置，它始终把“GL_TEXTURE_PROGRAM”状态定位到“Effect”对象的着色器上。
    // 此外，如果Effect使用了纹理，它也会修改“GL_TEXTURE_BINDING_2D”。
    [self.effect prepareToDraw];
    
    /**
     * 绘制方式，OpenGL2.0以后提供以下参数：
     * GL_POINTS - 单独的将顶点画出来。
     * GL_LINES - 单独地将直线画出来。行为和 GL_TRIANGLES 类似。
     * GL_LINE_STRIP - 连贯地将直线画出来。行为和 GL_TRIANGLE_STRIP 类似。
     * GL_LINE_LOOP - 连贯地将直线画出来。行为和 GL_LINE_STRIP 类似，但是会自动将最后一个顶点和第一个顶点通过直线连接起来。
     * GL_TRIANGLES - 这个参数意味着OpenGL使用三个顶点来组成图形。
                      第一个三角形使用顶点v0,v1,v2,第二个使用v3,v4,v5,以此类推。
                      如果顶点的个数n不是3的倍数，那么最后的1个或者2个顶点会被忽略。
     * GL_TRIANGLE_STRIP - OpenGL的使用将最开始的两个顶点出发，然后遍历每个顶点，这些顶点将使用前2个顶点一起组成一个三角形。
     * GL_TRIANGLE_FAN - 在跳过开始的2个顶点，然后遍历每个顶点，让OpenGL将这些顶点于它们前一个，以及数组的第一个顶点一起组成一个三角形。
     **/
    
    // 绑定VAO
    glBindVertexArrayOES(VAO);
    
    // 1.使用glDrawElements绘制
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    
    // 2.使用glDrawElements绘制，已经绑定EBO情况下，indices赋值0即可
    int count = sizeof(GL_ELEMENT_Indices) / sizeof(GL_ELEMENT_Indices[0]);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_BYTE, 0);
    
    // 绘制完毕，解绑VAO
    glBindVertexArrayOES(0);
}

- (void)dealloc
{
    if (VAO) {
        glDeleteVertexArraysOES(1, &VAO);
        VAO = 0;
    }
    if (VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (EBO) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
}

@end
