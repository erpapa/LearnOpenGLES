#version 300 es
precision highp float;
out vec4 FragColor;

uniform vec3 objectColor; // 物体颜色
uniform vec3 ambientColor; // 环境光

void main()
{
    vec3 result = ambientColor * objectColor;
    FragColor = vec4(result, 1.0);
}
