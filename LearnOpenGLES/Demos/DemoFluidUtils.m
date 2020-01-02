//
//  DemoFluidUtils.m
//  LearnOpenGLES
//
//  Created by apple on 2019/8/30.
//  Copyright © 2019 erpapa. All rights reserved.
//

#import "DemoFluidUtils.h"

NSString *const kFluidBaseVertexShaderString = @"\
precision highp float;\n\
\n\
attribute vec2 aPosition;\n\
varying vec2 vUv;\n\
varying vec2 vL;\n\
varying vec2 vR;\n\
varying vec2 vT;\n\
varying vec2 vB;\n\
uniform vec2 texelSize;\n\
\n\
void main () {\n\
    vUv = aPosition * 0.5 + 0.5;\n\
    vL = vUv - vec2(texelSize.x, 0.0);\n\
    vR = vUv + vec2(texelSize.x, 0.0);\n\
    vT = vUv + vec2(0.0, texelSize.y);\n\
    vB = vUv - vec2(0.0, texelSize.y);\n\
    gl_Position = vec4(aPosition, 0.0, 1.0);\n\
}\n\
";

NSString *const kFluidBlurVertexShaderString = @"\
precision highp float;\n\
\n\
attribute vec2 aPosition;\n\
varying vec2 vUv;\n\
varying vec2 vL;\n\
varying vec2 vR;\n\
uniform vec2 texelSize;\n\
\n\
void main () {\n\
    vUv = aPosition * 0.5 + 0.5;\n\
    float offset = 1.33333333;\n\
    vL = vUv - texelSize * offset;\n\
    vR = vUv + texelSize * offset;\n\
    gl_Position = vec4(aPosition, 0.0, 1.0);\n\
}\n\
";

NSString *const kFluidBlurFragmentShaderString = @"\
precision mediump float;\n\
precision mediump sampler2D;\n\
\n\
varying vec2 vUv;\n\
varying vec2 vL;\n\
varying vec2 vR;\n\
uniform sampler2D uTexture;\n\
\n\
void main () {\n\
    vec4 sum = texture2D(uTexture, vUv) * 0.29411764;\n\
    sum += texture2D(uTexture, vL) * 0.35294117;\n\
    sum += texture2D(uTexture, vR) * 0.35294117;\n\
    gl_FragColor = sum;\n\
}\n\
";

NSString *const kFluidCopyFragmentShaderString = @"\
precision mediump float;\n\
precision mediump sampler2D;\n\
\n\
varying highp vec2 vUv;\n\
uniform sampler2D uTexture;\n\
\n\
void main () {\n\
    gl_FragColor = texture2D(uTexture, vUv);\n\
}\n\
";

NSString *const kFluidClearFragmentShaderString = @"\
precision mediump float;\n\
precision mediump sampler2D;\n\
\n\
varying highp vec2 vUv;\n\
uniform sampler2D uTexture;\n\
uniform float value;\n\
\n\
void main () {\n\
    gl_FragColor = value * texture2D(uTexture, vUv);\n\
}\n\
";

NSString *const kFluidColorFragmentShaderString = @"\
precision mediump float;\n\
uniform vec4 color;\n\
\n\
void main () {\n\
    gl_FragColor = color;\n\
}\n\
";

NSString *const kFluidCheckerBoardFragmentShaderString = @"\
precision highp float;\n\
precision highp sampler2D;\n\
\n\
varying vec2 vUv;\n\
uniform sampler2D uTexture;\n\
uniform float aspectRatio;\n\
\n\
void main () {\n\
    vec2 uv = floor(vUv * 25.0 * vec2(aspectRatio, 1.0));\n\
    float v = mod(uv.x + uv.y, 2.0);\n\
    v = v * 0.1 + 0.8;\n\
    gl_FragColor = vec4(vec3(v), 1.0);\n\
}\n\
";

NSString *const kFluidDisplayFragmentShaderString = @"\
precision highp float;\n\
precision highp sampler2D;\n\
\n\
varying vec2 vUv;\n\
varying vec2 vL;\n\
varying vec2 vR;\n\
varying vec2 vT;\n\
varying vec2 vB;\n\
uniform sampler2D uTexture;\n\
uniform sampler2D uBloom;\n\
uniform sampler2D uSunrays;\n\
uniform sampler2D uDithering;\n\
uniform vec2 ditherScale;\n\
uniform vec2 texelSize;\n\
\n\
vec3 linearToGamma (vec3 color) {\n\
    color = max(color, vec3(0));\n\
    return max(1.055 * pow(color, vec3(0.416666667)) - 0.055, vec3(0));\n\
}\n\
\n\
void main () {\n\
    vec3 c = texture2D(uTexture, vUv).rgb;\n\
\n\
#ifdef SHADING\n\
\n\
    vec3 lc = texture2D(uTexture, vL).rgb;\n\
    vec3 rc = texture2D(uTexture, vR).rgb;\n\
    vec3 tc = texture2D(uTexture, vT).rgb;\n\
    vec3 bc = texture2D(uTexture, vB).rgb;\n\
\n\
    float dx = length(rc) - length(lc);\n\
    float dy = length(tc) - length(bc);\n\
\n\
    vec3 n = normalize(vec3(dx, dy, length(texelSize)));\n\
    vec3 l = vec3(0.0, 0.0, 1.0);\n\
\n\
    float diffuse = clamp(dot(n, l) + 0.7, 0.7, 1.0);\n\
    c *= diffuse;\n\
\n\
#endif\n\
\n\
#ifdef BLOOM\n\
\n\
    vec3 bloom = texture2D(uBloom, vUv).rgb;\n\
\n\
#endif\n\
\n\
#ifdef SUNRAYS\n\
\n\
    float sunrays = texture2D(uSunrays, vUv).r;\n\
    c *= sunrays;\n\
\n\
#ifdef BLOOM\n\
\n\
    bloom *= sunrays;\n\
\n\
#endif\n\
\n\
#endif\n\
\n\
#ifdef BLOOM\n\
\n\
    float noise = texture2D(uDithering, vUv * ditherScale).r;\n\
    noise = noise * 2.0 - 1.0;\n\
    bloom += noise / 255.0;\n\
    bloom = linearToGamma(bloom);\n\
    c += bloom;\n\
\n\
#endif\n\
\n\
    float a = max(c.r, max(c.g, c.b));\n\
    gl_FragColor = vec4(c, a);\n\
\n\
}\n\
";

NSString *const kFluidBloomPrefilterFragmentShaderString = @"\
precision mediump float;\n\
precision mediump sampler2D;\n\
\n\
varying vec2 vUv;\n\
uniform sampler2D uTexture;\n\
uniform vec3 curve;\n\
uniform float threshold;\n\
\n\
void main () {\n\
    vec3 c = texture2D(uTexture, vUv).rgb;\n\
    float br = max(c.r, max(c.g, c.b));\n\
    float rq = clamp(br - curve.x, 0.0, curve.y);\n\
    rq = curve.z * rq * rq;\n\
    c *= max(rq, br - threshold) / max(br, 0.0001);\n\
    gl_FragColor = vec4(c, 0.0);\n\
}\n\
";

NSString *const kFluidBloomBlurFragmentShaderString = @"\
precision mediump float;\n\
precision mediump sampler2D;\n\
\n\
varying vec2 vL;\n\
varying vec2 vR;\n\
varying vec2 vT;\n\
varying vec2 vB;\n\
uniform sampler2D uTexture;\n\
\n\
void main () {\n\
    vec4 sum = vec4(0.0);\n\
    sum += texture2D(uTexture, vL);\n\
    sum += texture2D(uTexture, vR);\n\
    sum += texture2D(uTexture, vT);\n\
    sum += texture2D(uTexture, vB);\n\
    sum *= 0.25;\n\
    gl_FragColor = sum;\n\
}\n\
";

NSString *const kFluidBloomFinalFragmentShaderString = @"\
precision mediump float;\n\
precision mediump sampler2D;\n\
\n\
varying vec2 vL;\n\
varying vec2 vR;\n\
varying vec2 vT;\n\
varying vec2 vB;\n\
uniform sampler2D uTexture;\n\
uniform float intensity;\n\
\n\
void main () {\n\
    vec4 sum = vec4(0.0);\n\
    sum += texture2D(uTexture, vL);\n\
    sum += texture2D(uTexture, vR);\n\
    sum += texture2D(uTexture, vT);\n\
    sum += texture2D(uTexture, vB);\n\
    sum *= 0.25;\n\
    gl_FragColor = sum * intensity;\n\
}\n\
";

NSString *const kFluidSunraysMaskFragmentShaderString = @"\
precision highp float;\n\
precision highp sampler2D;\n\
\n\
varying vec2 vUv;\n\
uniform sampler2D uTexture;\n\
\n\
void main () {\n\
    vec4 c = texture2D(uTexture, vUv);\n\
    float br = max(c.r, max(c.g, c.b));\n\
    c.a = 1.0 - min(max(br * 20.0, 0.0), 0.8);\n\
    gl_FragColor = c;\n\
}\n\
";

NSString *const kFluidSunraysFragmentShaderString = @"\
precision highp float;\n\
precision highp sampler2D;\n\
\n\
varying vec2 vUv;\n\
uniform sampler2D uTexture;\n\
uniform float weight;\n\
\n\
void main () {\n\
    float Density = 0.3;\n\
    float Decay = 0.95;\n\
    float Exposure = 0.7;\n\
\n\
    vec2 coord = vUv;\n\
    vec2 dir = vUv - 0.5;\n\
\n\
    dir *= 1.0 / 16.0 * Density;\n\
    float illuminationDecay = 1.0;\n\
\n\
    float color = texture2D(uTexture, vUv).a;\n\
\n\
    for (int i = 0; i < 16; i++)\n\
    {\n\
        coord -= dir;\n\
        float col = texture2D(uTexture, coord).a;\n\
        color += col * illuminationDecay * weight;\n\
        illuminationDecay *= Decay;\n\
    }\n\
\n\
    gl_FragColor = vec4(color * Exposure, 0.0, 0.0, 1.0);\n\
}\n\
";

NSString *const kFluidSplatFragmentShaderString = @"\
precision highp float;\n\
precision highp sampler2D;\n\
\n\
varying vec2 vUv;\n\
uniform sampler2D uTarget;\n\
uniform float aspectRatio;\n\
uniform vec3 color;\n\
uniform vec2 point;\n\
uniform float radius;\n\
\n\
void main () {\n\
    vec2 p = vUv - point.xy;\n\
    p.x *= aspectRatio;\n\
    vec3 splat = exp(-dot(p, p) / radius) * color;\n\
    vec3 base = texture2D(uTarget, vUv).xyz;\n\
    gl_FragColor = vec4(base + splat, 1.0);\n\
}\n\
";

NSString *const kFluidAdvectionFragmentShaderString = @"\
precision highp float;\n\
precision highp sampler2D;\n\
\n\
varying vec2 vUv;\n\
uniform sampler2D uVelocity;\n\
uniform sampler2D uSource;\n\
uniform vec2 texelSize;\n\
uniform vec2 dyeTexelSize;\n\
uniform float dt;\n\
uniform float dissipation;\n\
\n\
vec4 bilerp (sampler2D sam, vec2 uv, vec2 tsize) {\n\
    vec2 st = uv / tsize - 0.5;\n\
    vec2 iuv = floor(st);\n\
    vec2 fuv = fract(st);\n\
\n\
    vec4 a = texture2D(sam, (iuv + vec2(0.5, 0.5)) * tsize);\n\
    vec4 b = texture2D(sam, (iuv + vec2(1.5, 0.5)) * tsize);\n\
    vec4 c = texture2D(sam, (iuv + vec2(0.5, 1.5)) * tsize);\n\
    vec4 d = texture2D(sam, (iuv + vec2(1.5, 1.5)) * tsize);\n\
    return mix(mix(a, b, fuv.x), mix(c, d, fuv.x), fuv.y);\n\
}\n\
\n\
void main () {\n\
\n\
#ifdef MANUAL_FILTERING\n\
    vec2 coord = vUv - dt * bilerp(uVelocity, vUv, texelSize).xy * texelSize;\n\
    vec4 result = bilerp(uSource, coord, dyeTexelSize);\n\
#else\n\
    vec2 coord = vUv - dt * texture2D(uVelocity, vUv).xy * texelSize;\n\
    vec4 result = texture2D(uSource, coord);\n\
#endif\n\
    gl_FragColor = vec4(dissipation * result.rgb, 1.0);\n\
}\n\
";

NSString *const kFluidDivergenceFragmentShaderString = @"\
precision mediump float;\n\
precision mediump sampler2D;\n\
\n\
varying highp vec2 vUv;\n\
varying highp vec2 vL;\n\
varying highp vec2 vR;\n\
varying highp vec2 vT;\n\
varying highp vec2 vB;\n\
uniform sampler2D uVelocity;\n\
\n\
void main () {\n\
    float L = texture2D(uVelocity, vL).x;\n\
    float R = texture2D(uVelocity, vR).x;\n\
    float T = texture2D(uVelocity, vT).y;\n\
    float B = texture2D(uVelocity, vB).y;\n\
\n\
    vec2 C = texture2D(uVelocity, vUv).xy;\n\
    if (vL.x < 0.0) { L = -C.x; }\n\
    if (vR.x > 1.0) { R = -C.x; }\n\
    if (vT.y > 1.0) { T = -C.y; }\n\
    if (vB.y < 0.0) { B = -C.y; }\n\
\n\
    float div = 0.5 * (R - L + T - B);\n\
    gl_FragColor = vec4(div, 0.0, 0.0, 1.0);\n\
}\n\
";

NSString *const kFluidCurlFragmentShaderString = @"\
precision mediump float;\n\
precision mediump sampler2D;\n\
\n\
varying highp vec2 vUv;\n\
varying highp vec2 vL;\n\
varying highp vec2 vR;\n\
varying highp vec2 vT;\n\
varying highp vec2 vB;\n\
uniform sampler2D uVelocity;\n\
\n\
void main () {\n\
    float L = texture2D(uVelocity, vL).y;\n\
    float R = texture2D(uVelocity, vR).y;\n\
    float T = texture2D(uVelocity, vT).x;\n\
    float B = texture2D(uVelocity, vB).x;\n\
    float vorticity = R - L - T + B;\n\
    gl_FragColor = vec4(0.5 * vorticity, 0.0, 0.0, 1.0);\n\
}\n\
";

NSString *const kFluidVorticityFragmentShaderString = @"\
precision highp float;\n\
precision highp sampler2D;\n\
\n\
varying vec2 vUv;\n\
varying vec2 vL;\n\
varying vec2 vR;\n\
varying vec2 vT;\n\
varying vec2 vB;\n\
uniform sampler2D uVelocity;\n\
uniform sampler2D uCurl;\n\
uniform float curl;\n\
uniform float dt;\n\
\n\
void main () {\n\
    float L = texture2D(uCurl, vL).x;\n\
    float R = texture2D(uCurl, vR).x;\n\
    float T = texture2D(uCurl, vT).x;\n\
    float B = texture2D(uCurl, vB).x;\n\
    float C = texture2D(uCurl, vUv).x;\n\
\n\
    vec2 force = 0.5 * vec2(abs(T) - abs(B), abs(R) - abs(L));\n\
    force /= length(force) + 0.0001;\n\
    force *= curl * C;\n\
    force.y *= -1.0;\n\
\n\
    vec2 vel = texture2D(uVelocity, vUv).xy;\n\
    gl_FragColor = vec4(vel + force * dt, 0.0, 1.0);\n\
}\n\
";

NSString *const kFluidPressureFragmentShaderString = @"\
precision mediump float;\n\
precision mediump sampler2D;\n\
\n\
varying highp vec2 vUv;\n\
varying highp vec2 vL;\n\
varying highp vec2 vR;\n\
varying highp vec2 vT;\n\
varying highp vec2 vB;\n\
uniform sampler2D uPressure;\n\
uniform sampler2D uDivergence;\n\
\n\
void main () {\n\
    float L = texture2D(uPressure, vL).x;\n\
    float R = texture2D(uPressure, vR).x;\n\
    float T = texture2D(uPressure, vT).x;\n\
    float B = texture2D(uPressure, vB).x;\n\
    float C = texture2D(uPressure, vUv).x;\n\
    float divergence = texture2D(uDivergence, vUv).x;\n\
    float pressure = (L + R + B + T - divergence) * 0.25;\n\
    gl_FragColor = vec4(pressure, 0.0, 0.0, 1.0);\n\
}\n\
";

NSString *const kFluidGradientSubtractFragmentShaderString = @"\
precision mediump float;\n\
precision mediump sampler2D;\n\
\n\
varying highp vec2 vUv;\n\
varying highp vec2 vL;\n\
varying highp vec2 vR;\n\
varying highp vec2 vT;\n\
varying highp vec2 vB;\n\
uniform sampler2D uPressure;\n\
uniform sampler2D uVelocity;\n\
\n\
void main () {\n\
    float L = texture2D(uPressure, vL).x;\n\
    float R = texture2D(uPressure, vR).x;\n\
    float T = texture2D(uPressure, vT).x;\n\
    float B = texture2D(uPressure, vB).x;\n\
    vec2 velocity = texture2D(uVelocity, vUv).xy;\n\
    velocity.xy -= vec2(R - L, T - B);\n\
    gl_FragColor = vec4(velocity, 0.0, 1.0);\n\
}\n\
";

@implementation FluidPointer

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.id = -1;
        self.texcoordX = 0;
        self.texcoordY = 0;
        self.prevTexcoordX = 0;
        self.prevTexcoordY = 0;
        self.deltaX = 0;
        self.deltaY = 0;
        self.down = NO;
        self.moved = NO;
        self.color = (FluidColor){0.1176, 0, 0.7843};
    }
    return self;
}

@end

@implementation FluidFrameBuffer

- (instancetype)init
{
    return [self initWithWidth:1 height:1 internalFormat:GL_RGBA format:GL_RGBA type:GL_HALF_FLOAT_OES param:GL_LINEAR];
}

- (instancetype)initWithWidth:(int)width height:(int)height internalFormat:(GLenum)internalFormat format:(GLenum)format type:(GLenum)type param:(GLint)param
{
    self = [super init];
    if (self) {
        _width = width;
        _height = height;
        _internalFormat = internalFormat;
        _format = format;
        _type = type;
        _param = param;
        _texelSizeX = 1.0 / width;
        _texelSizeY = 1.0 / height;
        
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);
        glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _format, _type, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _param);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _param);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        glGenFramebuffers(1, &_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
        glViewport(0, 0, _width, _height);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        NSAssert(status == GL_FRAMEBUFFER_COMPLETE, @"Incomplete filter FBO: %d", status);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    return self;
}

- (void)dealloc
{
    if (_texture) {
        glDeleteTextures(1, &_texture);
        _texture = 0;
    }
    if (_fbo) {
        glDeleteFramebuffers(1, &_fbo);
        _fbo = 0;
    }
}

@end

@implementation FluidDoubleFrameBuffer

- (instancetype)init
{
    return [self initWithWidth:1 height:1 internalFormat:GL_RGBA16F_EXT format:GL_RGBA type:GL_HALF_FLOAT_OES param:GL_LINEAR];
}

- (instancetype)initWithWidth:(int)width height:(int)height internalFormat:(GLenum)internalFormat format:(GLenum)format type:(GLenum)type param:(GLint)param
{
    self = [super init];
    if (self) {
        _width = width;
        _height = height;
        _internalFormat = internalFormat;
        _format = format;
        _type = type;
        _param = param;
        _texelSizeX = 1.0 / width;
        _texelSizeY = 1.0 / height;
        self.read = [[FluidFrameBuffer alloc] initWithWidth:_width height:_height internalFormat:_internalFormat format:_format type:_type param:_param];
        self.write = [[FluidFrameBuffer alloc] initWithWidth:_width height:_height internalFormat:_internalFormat format:_format type:_type param:_param];
    }
    return self;
}

- (void)swap
{
    FluidFrameBuffer *temp = self.read;
    self.read = self.write;
    self.write = temp;
}

@end

@implementation FluidProgram

- (instancetype)initWithVertexShaderString:(NSString *)vShaderString fragmentShaderString:(NSString *)fShaderString
{
    self = [super init];
    if (self) {
        _vertexShaderString = vShaderString;
        _fragmentShaderString = fShaderString;
        
        GLProgram *program = [[GLProgram alloc] initWithVertexShaderString:vShaderString fragmentShaderString:fShaderString];
        [program addAttribute:@"aPosition"];
        [program link];
        NSMutableDictionary *programs = [NSMutableDictionary dictionary];
        [programs setObject:program forKey:[NSNumber numberWithUnsignedInteger:0]];
        _programs = [programs copy];
        _activeProgram = program;
        _uniforms = nil;
    }
    return self;
}

- (void)setKeywords:(NSArray *)keywords
{
    NSUInteger hash = 0;
    NSMutableString *shaderString = [NSMutableString string];
    for (NSString *word in keywords) {
        hash += word.hash;
        [shaderString appendString:[NSString stringWithFormat:@"#define %@\n", word]];
    }
    GLProgram *program = [self.programs objectForKey:[NSNumber numberWithUnsignedInteger:hash]];
    if (program == nil) {
        [shaderString appendString:self.fragmentShaderString];
        program = [[GLProgram alloc] initWithVertexShaderString:self.vertexShaderString fragmentShaderString:[shaderString copy]];
        [program addAttribute:@"aPosition"];
        [program link];
        NSMutableDictionary *programs = [NSMutableDictionary dictionaryWithDictionary:self.programs];
        [programs setObject:program forKey:[NSNumber numberWithUnsignedInteger:hash]];
        _programs = [programs copy];
    }
    if (program == self.activeProgram) {
        return;
    }
    _activeProgram = program;
    _uniforms = nil;
}

- (GLuint)uniformIndex:(NSString *)uniformName
{
    NSNumber *uniformValue = [self.uniforms objectForKey:uniformName];
    if (uniformValue == nil) {
        uniformValue = [NSNumber numberWithInt:[self.activeProgram uniformIndex:uniformName]];
        NSMutableDictionary *uniforms = [NSMutableDictionary dictionaryWithDictionary:self.uniforms];
        [uniforms setObject:uniformValue forKey:uniformName];
        _uniforms = [uniforms copy];
    }
    GLuint uniform = [uniformValue intValue];
    NSAssert(uniform >= 0, @"Undefined: %@", uniformName);
    return uniform;
}

- (void)use
{
    [self.activeProgram use];
}

@end
