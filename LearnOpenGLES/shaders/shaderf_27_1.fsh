#version 300 es
#define NR_POINT_LIGHTS 4
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

struct DirLight
{
    vec4 direction;
    
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight
{
    vec4 position;
    
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec4 position;
    vec4 direction;
    
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(ViewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    // phase 3: spot light
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(vec3(-light.direction));
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = vec3(light.ambient) * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = vec3(light.specular) * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(vec3(light.position) - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float dist = length(vec3(light.position) - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    // combine results
    vec3 ambient = vec3(light.ambient) * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = vec3(light.specular) * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(vec3(light.position) - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float dist = length(vec3(light.position) - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    // spotlight intensity
    float theta = dot(lightDir, normalize(vec3(-light.direction)));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = vec3(light.ambient) * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = vec3(light.specular) * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
