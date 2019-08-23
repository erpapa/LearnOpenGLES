attribute vec4 position;
attribute vec4 inputTextureCoordinate;
varying vec2 textureCoordinate;

uniform float inputTime;
varying float alphaLevel;
varying vec2 rCoord;
varying vec2 gCoord;
varying vec2 bCoord;

const float PI = 3.1415926;
const float duration = 0.8;

void main()
{
    float ff = mod(inputTime, duration) / duration;
    float percent = sin((1.0 - ff) * (PI * 0.5));
    alphaLevel = 0.4 * percent;
    
    float scale = 0.45 + 0.5 * percent;
    mat4 transform = mat4(scale, 0.0, 0.0, 0.0, 0.0, scale, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    mat4 offsetMat = transform;
    vec4 coord = inputTextureCoordinate - vec4(0.5,0.5,0.5,0);
    rCoord = (transform * coord).xy + vec2(0.5);
    transform = offsetMat*transform;
    gCoord = (transform * coord).xy + vec2(0.5);
    transform = offsetMat*transform;
    bCoord = (transform * coord).xy + vec2(0.5);
	textureCoordinate = inputTextureCoordinate.xy;
	gl_Position = position;
}
