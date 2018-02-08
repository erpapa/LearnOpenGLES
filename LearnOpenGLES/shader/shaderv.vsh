attribute vec4 position;
attribute vec4 inputTextureCoordinate;

uniform mat4 transformMatrix;

varying vec2 textureCoordinate;

void main()
{
    textureCoordinate = inputTextureCoordinate.xy;
    gl_Position = transformMatrix * position;
}
