//
//  DemoUtils.h
//  LearnOpenGLES
//
//  Created by apple on 2019/8/14.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface DemoUtils : NSObject

// 渲染bitmap
+ (CGImageRef)renderBitmapData:(NSData *)bitmapData width:(NSInteger)width height:(NSInteger)height;
+ (CGImageRef)renderBitmapData:(NSData *)bitmapData width:(NSInteger)width height:(NSInteger)height colorSpace:(CGColorSpaceRef)colorSpace;

// 创建bitmap
+ (NSData *)createBitmapFromImage:(CGImageRef)image;
+ (NSData *)createBitmapFromImage:(CGImageRef)image flippedX:(BOOL)flippedX flippedY:(BOOL)flippedY;

// 创建纹理
+ (GLuint)createTextureFromImage:(CGImageRef)image;
+ (GLuint)createTextureFromImage:(CGImageRef)image flippedX:(BOOL)flippedX flippedY:(BOOL)flippedY;

// 创建program
+ (GLuint)createProgram;

// 编译shader
+ (GLuint)compileShaderPath:(NSString *)shaderFile type:(GLenum)type;
+ (GLuint)compileShaderString:(NSString *)shaderString type:(GLenum)type;

// 执行attach
+ (void)attachShader:(GLuint)program shader:(GLuint)shader;
+ (void)attachShader:(GLuint)program vertShader:(GLint)vertShader fragShader:(GLint)fragShader;

// GLES2 需要绑定 attribLocation，GLES3 可以直接在顶点着色器指定 layout
+ (void)bindAttribLocation:(GLuint)program index:(GLuint)index name:(NSString *)name;

// 链接program，然后删除shader
+ (BOOL)linkProgram:(GLuint)program vertShader:(GLint)vertShader fragShader:(GLint)fragShader;

// 使用program
+ (void)useProgram:(GLuint)program;

// 删除program
+ (void)deleteProgram:(GLuint)program;

@end
