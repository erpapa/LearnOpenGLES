attribute vec4 position;
attribute vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec3 positionVarying;
varying vec3 normalVarying;

void main()
{
    positionVarying = vec3(model * position);
    normalVarying = normal;
    gl_Position = projection * view * model * position;
}
