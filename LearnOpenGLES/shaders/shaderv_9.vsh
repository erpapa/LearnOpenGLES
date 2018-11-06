attribute highp vec4 position;

varying highp vec3 textureCoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    textureCoordinate = position.xyz;
    gl_Position = projection * view * model * vec4(position.xyz, 1.0);
}
