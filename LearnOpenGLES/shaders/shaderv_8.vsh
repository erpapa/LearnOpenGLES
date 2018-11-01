attribute highp vec4 position;
attribute highp vec4 inputTextureCoordinate;

varying highp vec2 textureCoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    textureCoordinate = inputTextureCoordinate.xy;
    gl_Position = projection * view * model * vec4(position.xyz, 1.0);
}
