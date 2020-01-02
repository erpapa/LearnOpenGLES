//
//  DemoFluidUtils.h
//  LearnOpenGLES
//
//  Created by apple on 2019/8/30.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <CoreGraphics/CoreGraphics.h>
#import "GLProgram.h"

extern NSString *const kFluidBaseVertexShaderString;
extern NSString *const kFluidBlurVertexShaderString;

extern NSString *const kFluidBlurFragmentShaderString;
extern NSString *const kFluidCopyFragmentShaderString;
extern NSString *const kFluidClearFragmentShaderString;
extern NSString *const kFluidColorFragmentShaderString;
extern NSString *const kFluidCheckerBoardFragmentShaderString;
extern NSString *const kFluidDisplayFragmentShaderString;
extern NSString *const kFluidBloomPrefilterFragmentShaderString;
extern NSString *const kFluidBloomBlurFragmentShaderString;
extern NSString *const kFluidBloomFinalFragmentShaderString;
extern NSString *const kFluidSunraysMaskFragmentShaderString;
extern NSString *const kFluidSunraysFragmentShaderString;
extern NSString *const kFluidSplatFragmentShaderString;
extern NSString *const kFluidAdvectionFragmentShaderString;
extern NSString *const kFluidDivergenceFragmentShaderString;
extern NSString *const kFluidCurlFragmentShaderString;
extern NSString *const kFluidVorticityFragmentShaderString;
extern NSString *const kFluidPressureFragmentShaderString;
extern NSString *const kFluidGradientSubtractFragmentShaderString;

#pragma mark - Color

union _FluidColor
{
    struct { float r, g, b; };
    float v[3];
};
typedef union _FluidColor FluidColor;

#pragma mark - Format

struct _FluidFormat {
    GLenum internalFormat;
    GLenum format;
};
typedef struct _FluidFormat FluidFormat;

#pragma mark - Extension

struct _FluidExtension {
    FluidFormat formatRGBA;
    FluidFormat formatRG;
    FluidFormat formatR;
    GLenum halfFloatTexType;
    BOOL supportLinearFiltering;
};
typedef struct _FluidExtension FluidExtension;

#pragma mark - Config

struct _FluidConfig {
    NSInteger SIM_RESOLUTION;
    NSInteger DYE_RESOLUTION;
    NSInteger CAPTURE_RESOLUTION;
    float DENSITY_DISSIPATION;
    float VELOCITY_DISSIPATION;
    float PRESSURE_DISSIPATION;
    NSInteger PRESSURE_ITERATIONS;
    NSInteger CURL;
    CGFloat SPLAT_RADIUS;
    NSInteger SPLAT_FORCE;
    BOOL SHADING;
    BOOL COLORFUL;
    CGFloat COLOR_UPDATE_SPEED;
    BOOL PAUSED;
    FluidColor BACK_COLOR;
    BOOL TRANSPARENT;
    BOOL BLOOM;
    NSInteger BLOOM_ITERATIONS;
    NSInteger BLOOM_RESOLUTION;
    CGFloat BLOOM_INTENSITY;
    CGFloat BLOOM_THRESHOLD;
    CGFloat BLOOM_SOFT_KNEE;
    BOOL SUNRAYS;
    NSInteger SUNRAYS_RESOLUTION;
    CGFloat SUNRAYS_WEIGHT;
};
typedef struct _FluidConfig FluidConfig;

@interface FluidPointer : NSObject

@property (nonatomic, assign) int id;
@property (nonatomic, assign) float texcoordX;
@property (nonatomic, assign) float texcoordY;
@property (nonatomic, assign) float prevTexcoordX;
@property (nonatomic, assign) float prevTexcoordY;
@property (nonatomic, assign) float deltaX;
@property (nonatomic, assign) float deltaY;
@property (nonatomic, assign) BOOL down;
@property (nonatomic, assign) BOOL moved;
@property (nonatomic, assign) FluidColor color;

@end

@interface FluidFrameBuffer : NSObject

@property (nonatomic, assign, readonly) GLuint texture;
@property (nonatomic, assign, readonly) GLuint fbo;
@property (nonatomic, assign, readonly) int width;
@property (nonatomic, assign, readonly) int height;
@property (nonatomic, assign, readonly) GLenum internalFormat;
@property (nonatomic, assign, readonly) GLenum format;
@property (nonatomic, assign, readonly) GLenum type;
@property (nonatomic, assign, readonly) GLint param;

@property (nonatomic, assign, readonly) float texelSizeX;
@property (nonatomic, assign, readonly) float texelSizeY;

- (instancetype)initWithWidth:(int)width height:(int)height internalFormat:(GLenum)internalFormat format:(GLenum)format type:(GLenum)type param:(GLint)param;

@end

@interface FluidDoubleFrameBuffer : NSObject

@property (nonatomic, strong) FluidFrameBuffer *read;
@property (nonatomic, strong) FluidFrameBuffer *write;

@property (nonatomic, assign, readonly) int width;
@property (nonatomic, assign, readonly) int height;
@property (nonatomic, assign, readonly) GLenum internalFormat;
@property (nonatomic, assign, readonly) GLenum format;
@property (nonatomic, assign, readonly) GLenum type;
@property (nonatomic, assign, readonly) GLint param;

@property (nonatomic, assign, readonly) float texelSizeX;
@property (nonatomic, assign, readonly) float texelSizeY;

- (instancetype)initWithWidth:(int)width height:(int)height internalFormat:(GLenum)internalFormat format:(GLenum)format type:(GLenum)type param:(GLint)param;

- (void)swap;

@end

@interface FluidProgram : NSObject

@property (nonatomic, copy, readonly) NSString *vertexShaderString;
@property (nonatomic, copy, readonly) NSString *fragmentShaderString;

@property (nonatomic, strong, readonly) GLProgram *activeProgram;
@property (nonatomic, copy, readonly) NSDictionary *programs;
@property (nonatomic, copy, readonly) NSDictionary *uniforms;

- (instancetype)initWithVertexShaderString:(NSString *)vShaderString fragmentShaderString:(NSString *)fShaderString;
- (void)setKeywords:(NSArray *)keywords;

- (GLuint)uniformIndex:(NSString *)uniformName;
- (void)use;

@end
