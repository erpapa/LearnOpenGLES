precision highp float;

uniform vec3 objectColor; // 物体颜色
uniform vec3 ambientColor; // 环境光
uniform vec3 lightColor; // 灯光颜色
uniform vec3 lightPosition; // 灯光位置

varying vec3 positionVarying; // 物体坐标
varying vec3 normalVarying; // 法向量

void main()
{
    // 1.环境光
    vec3 ambient = ambientColor;
    
    // 2.漫反射光
    // 计算光源向量，规范化两个向量
    vec3 norm = normalize(normalVarying);
    vec3 lightDir = normalize(lightPosition - positionVarying);
    
    // 计算点积，修正点积值，乘上光源颜色值
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 result = (ambient + diffuse) * objectColor;
    gl_FragColor = vec4(result, 1.0);
}
