//
//  DemoUtils.m
//  LearnOpenGLES
//
//  Created by apple on 2019/8/14.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoUtils.h"

@implementation DemoUtils

+ (CGImageRef)renderBitmapData:(NSData *)bitmapData width:(NSInteger)width height:(NSInteger)height;
{
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGImageRef cgImage = [self renderBitmapData:bitmapData width:width height:height colorSpace:colorSpace];
    CGColorSpaceRelease(colorSpace);
    return cgImage;
}

+ (CGImageRef)renderBitmapData:(NSData *)bitmapData width:(NSInteger)width height:(NSInteger)height colorSpace:(CGColorSpaceRef)colorSpace
{
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    
    CGDataProviderRef dataProvider = CGDataProviderCreateWithData(NULL, bitmapData.bytes, width * height * 4, NULL);
    CGImageRef cgImgage = CGImageCreate(width, height, 8, 8 * 4, width * 4, colorSpace, bitmapInfo, dataProvider, NULL, NO, renderingIntent);
    CGDataProviderRelease(dataProvider);
    return cgImgage;
}

+ (NSData *)createBitmapFromImage:(CGImageRef)image
{
    return [self createBitmapFromImage:image flippedX:NO flippedY:NO];
}

+ (NSData *)createBitmapFromImage:(CGImageRef)image flippedX:(BOOL)flippedX flippedY:(BOOL)flippedY
{
    CGContextRef context = NULL;
    CGColorSpaceRef colorSpace;
    unsigned char *bitmap;
    size_t bitmapSize;
    size_t bytesPerRow;
    
    size_t width = CGImageGetWidth(image);
    size_t height = CGImageGetHeight(image);
    
    bytesPerRow   = (width * 4);
    bitmapSize    = (bytesPerRow * height);
    
    bitmap = (unsigned char *)malloc(bitmapSize);
    if (bitmap == NULL)
    {
        return nil;
    }
    
    colorSpace = CGColorSpaceCreateDeviceRGB();
    if (colorSpace == NULL)
    {
        free(bitmap);
        return nil;
    }
    
    context = CGBitmapContextCreate(bitmap,
                                    width,
                                    height,
                                    8,
                                    bytesPerRow,
                                    colorSpace,
                                    kCGImageAlphaPremultipliedLast);
    
    CGColorSpaceRelease(colorSpace);
    
    if (context == NULL)
    {
        free(bitmap);
        return nil;
    }
    
    if (flippedX && flippedY)
    {
        CGContextTranslateCTM(context, width, height);
        CGContextScaleCTM(context, -1.0, -1.0);
    } else if (flippedX) {
        CGContextTranslateCTM(context, width, 0.0);
        CGContextScaleCTM(context, -1.0, 1.0);
    } else if (flippedY) {
        CGContextTranslateCTM(context, 0.0, height);
        CGContextScaleCTM(context, 1.0, -1.0);
    }
    
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), image);
    CGContextRelease(context);
    
    NSData *bitmapData = [NSData dataWithBytesNoCopy:bitmap length:bitmapSize freeWhenDone:YES];
    return bitmapData;
}

+ (GLuint)createTextureFromImage:(CGImageRef)image
{
    return [self createTextureFromImage:image flippedX:NO flippedY:NO];
}

+ (GLuint)createTextureFromImage:(CGImageRef)image flippedX:(BOOL)flippedX flippedY:(BOOL)flippedY
{
    // 1.从CGImage获取bitmap
    NSData *imageData = [self createBitmapFromImage:image flippedX:flippedX flippedY:flippedY];
    
    // 2、读取图片的大小，宽和高
    GLuint width = (GLuint)CGImageGetWidth(image);
    GLuint height = (GLuint)CGImageGetHeight(image);
    
    // 3. 生成纹理，绑定纹理ID
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // 4. 载入纹理2D数据
    /**
     * 参数1：纹理模式，GL_TEXTURE_1D、GL_TEXTURE_2D、GL_TEXTURE_3D
     * 参数2：加载的层次，一般设置为0
     * 参数3：纹理的颜色值GL_RGBA
     * 参数4：宽
     * 参数5：高
     * 参数6：border，边界宽度
     * 参数7：format
     * 参数8：type
     * 参数9：纹理数据
     */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.bytes);
    
    // 5. 设置纹理属性
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 6. 解绑纹理
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // 7. 返回纹理ID
    return textureID;
}

+ (GLuint)createProgram
{
    return glCreateProgram();
}

+ (GLuint)compileShaderPath:(NSString *)shaderPath type:(GLenum)type
{
    NSError *error;
    NSString *shaderString = [NSString stringWithContentsOfFile:shaderPath encoding:NSUTF8StringEncoding error:&error];
    if (error)
    {
        NSLog(@"Failed to load shader string !");
        return 0;
    }
    return [self compileShaderString:shaderString type:type];
}

+ (GLuint)compileShaderString:(NSString *)shaderString type:(GLenum)type
{
    GLint status;
    const GLchar *source;
    source = (GLchar *)[shaderString UTF8String];
    if (!source)
    {
        NSLog(@"Failed to load shader string !");
        return NO;
    }
    
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE)
    {
        return shader;
    }
    
    GLint logLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(shader, logLength, &logLength, log);
        NSLog(@"%s", log);
        free(log);
    }
    return 0;
}

+ (void)attachShader:(GLuint)program shader:(GLuint)shader
{
    glAttachShader(program, shader);
}

+ (void)attachShader:(GLuint)program vertShader:(GLint)vertShader fragShader:(GLint)fragShader
{
    [self attachShader:program shader:vertShader];
    [self attachShader:program shader:fragShader];
}

+ (void)bindAttribLocation:(GLuint)program index:(GLuint)index name:(NSString *)name;
{
    glBindAttribLocation(program, index, [name UTF8String]);
}

+ (BOOL)linkProgram:(GLuint)program
{
    GLint status;
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        return NO;
    }
    return YES;
}

+ (void)deleteShader:(GLuint)shader
{
    if (shader)
    {
        glDeleteShader(shader);
    }
}

+ (void)useProgram:(GLuint)program
{
    glUseProgram(program);
}

+ (void)deleteProgram:(GLuint)program
{
    if (program)
    {
        glDeleteProgram(program);
    }
}

@end
