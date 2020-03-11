#version 300 es
precision highp float;

out vec4 FragColor;

in vec3 ViewPos;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material
{
    sampler2D diffuse; // 漫反射贴图
    sampler2D specular; // 镜面光贴图
    float shininess;
};

uniform Material material;

layout (std140) uniform Light
{
    // 使用vec4，字节对齐
    vec4 light_position;
    
    vec4 light_color;
    vec4 light_ambient;
    vec4 light_diffuse;
    vec4 light_specular;
};

void main()
{
    // 1.环境光
    vec3 ambient = vec3(light_color * light_ambient * texture(material.diffuse, TexCoords));
    
    // 2.漫反射光
    // 计算光源向量，规范化两个向量
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(light_position) - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(light_diffuse * (diff * texture(material.diffuse, TexCoords)));
    
    // 3.镜面高光
    // 计算反射光向量
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    // 计算镜面高光的强度，shininess表示了高光的光泽度信息。光泽度越高，高光范围越集中
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = vec3(light_specular * (spec * texture(material.specular, TexCoords)));
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
