precision highp float;

uniform vec3 objectColor; // 物体颜色
uniform vec3 ambientColor; // 环境光
uniform vec3 lightColor; // 灯光颜色
uniform vec3 lightPosition; // 灯光位置
uniform vec3 cameraPosition; // 摄像机位置

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
    
    // 3.镜面高光
    // 设置镜面反射强度
    float specularStrength = 0.5;
    // 计算反射光向量
    vec3 viewDir = normalize(cameraPosition - positionVarying);
    vec3 reflectDir = reflect(-lightDir, norm);
    // 计算镜面高光的强度，32表示了高光的光泽度信息。光泽度越高，高光范围越集中
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    gl_FragColor = vec4(result, 1.0);
}
