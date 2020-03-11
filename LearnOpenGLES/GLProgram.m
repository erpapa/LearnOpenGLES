//  This is Jeff LaMarche's GLProgram OpenGL shader wrapper class from his OpenGL ES 2.0 book.
//  A description of this can be found at his page on the topic:
//  http://iphonedevelopment.blogspot.com/2010/11/opengl-es-20-for-ios-chapter-4.html


#import "GLProgram.h"
// START:typedefs
#pragma mark Function Pointer Definitions
typedef void (*GLInfoFunction)(GLuint program, GLenum pname, GLint* params);
typedef void (*GLLogFunction) (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
// END:typedefs
#pragma mark -
#pragma mark Private Extension Method Declaration
// START:extension
@interface GLProgram()

- (BOOL)compileShader:(GLuint *)shader 
                 type:(GLenum)type 
               string:(NSString *)shaderString;
@end
// END:extension
#pragma mark -

@implementation GLProgram
// START:init

@synthesize initialized = _initialized;

- (id)initWithVertexShaderString:(NSString *)vShaderString 
            fragmentShaderString:(NSString *)fShaderString;
{
    if ((self = [super init])) 
    {
        _initialized = NO;
        
        _attributes = [[NSMutableArray alloc] init];
        _uniforms = [[NSMutableArray alloc] init];
        _program = glCreateProgram();
        
        if (![self compileShader:&_vertShader
                            type:GL_VERTEX_SHADER 
                          string:vShaderString])
        {
            NSLog(@"Failed to compile vertex shader");
        }
        
        // Create and compile fragment shader
        if (![self compileShader:&_fragShader
                            type:GL_FRAGMENT_SHADER 
                          string:fShaderString])
        {
            NSLog(@"Failed to compile fragment shader");
        }
        
        glAttachShader(_program, _vertShader);
        glAttachShader(_program, _fragShader);
    }
    
    return self;
}

- (id)initWithVertexShaderString:(NSString *)vShaderString 
          fragmentShaderFilename:(NSString *)fShaderFilename;
{
    NSString *fragShaderPathname = [[NSBundle mainBundle] pathForResource:fShaderFilename ofType:@"fsh"];
    NSString *fragmentShaderString = [NSString stringWithContentsOfFile:fragShaderPathname encoding:NSUTF8StringEncoding error:nil];
    
    if ((self = [self initWithVertexShaderString:vShaderString fragmentShaderString:fragmentShaderString])) 
    {
    }
    
    return self;
}

- (id)initWithVertexShaderFilename:(NSString *)vShaderFilename 
            fragmentShaderFilename:(NSString *)fShaderFilename;
{
    NSString *vertShaderPathname = [[NSBundle mainBundle] pathForResource:vShaderFilename ofType:@"vsh"];
    NSString *vertexShaderString = [NSString stringWithContentsOfFile:vertShaderPathname encoding:NSUTF8StringEncoding error:nil];

    NSString *fragShaderPathname = [[NSBundle mainBundle] pathForResource:fShaderFilename ofType:@"fsh"];
    NSString *fragmentShaderString = [NSString stringWithContentsOfFile:fragShaderPathname encoding:NSUTF8StringEncoding error:nil];
    
    if ((self = [self initWithVertexShaderString:vertexShaderString fragmentShaderString:fragmentShaderString])) 
    {
    }
    
    return self;
}
// END:init
// START:compile
- (BOOL)compileShader:(GLuint *)shader 
                 type:(GLenum)type 
               string:(NSString *)shaderString
{
//    CFAbsoluteTime startTime = CFAbsoluteTimeGetCurrent();

    GLint status;
    const GLchar *source;
    
    source = 
      (GLchar *)[shaderString UTF8String];
    if (!source)
    {
        NSLog(@"Failed to load vertex shader");
        return NO;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		GLint logLength;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			GLchar *log = (GLchar *)malloc(logLength);
			glGetShaderInfoLog(*shader, logLength, &logLength, log);
            if (shader == &_vertShader)
            {
                self.vertexShaderLog = [NSString stringWithFormat:@"%s", log];
            }
            else
            {
                self.fragmentShaderLog = [NSString stringWithFormat:@"%s", log];
            }

			free(log);
		}
	}	
	
//    CFAbsoluteTime linkTime = (CFAbsoluteTimeGetCurrent() - startTime);
//    NSLog(@"Compiled in %f ms", linkTime * 1000.0);

    return status == GL_TRUE;
}
// END:compile
#pragma mark -
// START:addattribute
- (void)addAttribute:(NSString *)attributeName
{
    if (![_attributes containsObject:attributeName])
    {
        [_attributes addObject:attributeName];
        glBindAttribLocation(_program,
                             (GLuint)[_attributes indexOfObject:attributeName],
                             [attributeName UTF8String]);
    }
}
// END:addattribute
// START:indexmethods
- (GLuint)attributeIndex:(NSString *)attributeName
{
    return (GLuint)[_attributes indexOfObject:attributeName];
}
- (GLuint)uniformIndex:(NSString *)uniformName
{
    return glGetUniformLocation(_program, [uniformName UTF8String]);
}
// END:indexmethods
#pragma mark -
// START:link
- (BOOL)link
{
//    CFAbsoluteTime startTime = CFAbsoluteTimeGetCurrent();

    GLint status;
    
    glLinkProgram(_program);
    
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
        return NO;
    
    if (_vertShader)
    {
        glDeleteShader(_vertShader);
        _vertShader = 0;
    }
    if (_fragShader)
    {
        glDeleteShader(_fragShader);
        _fragShader = 0;
    }
    
    self.initialized = YES;

//    CFAbsoluteTime linkTime = (CFAbsoluteTimeGetCurrent() - startTime);
//    NSLog(@"Linked in %f ms", linkTime * 1000.0);

    return YES;
}
// END:link
// START:use
- (void)use
{
    glUseProgram(_program);
}
// END:use
#pragma mark -

- (void)validate;
{
	GLint logLength;
	
	glValidateProgram(_program);
	glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = (GLchar *)malloc(logLength);
		glGetProgramInfoLog(_program, logLength, &logLength, log);
        self.programLog = [NSString stringWithFormat:@"%s", log];
		free(log);
	}	
}

#pragma mark -
// START:dealloc
- (void)dealloc
{
    if (_vertShader)
        glDeleteShader(_vertShader);
        
    if (_fragShader)
        glDeleteShader(_fragShader);
    
    if (_program)
        glDeleteProgram(_program);
       
}
// END:dealloc
@end
