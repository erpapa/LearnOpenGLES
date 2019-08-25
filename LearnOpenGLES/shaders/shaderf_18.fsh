precision highp float;

uniform vec3 objectColor; // 物体颜色
uniform vec3 ambientColor; // 环境光

void main()
{
    vec3 result = ambientColor * objectColor;
    gl_FragColor = vec4(result, 1.0);
}
