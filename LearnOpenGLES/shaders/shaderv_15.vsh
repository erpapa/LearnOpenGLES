attribute vec4 position;
attribute vec4 sourceColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec4 destinationColor;

void main()
{
    destinationColor = sourceColor;
    gl_Position = projection * view * model * position;
}
