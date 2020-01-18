#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 viewPos;
out vec3 FragPos;
out vec3 Normal;

layout (std140) uniform Model
{
    mat4 model_matrix;
};

layout (std140) uniform Camera
{
    // 使用vec4，字节对齐
    vec4 camera_position;
    mat4 camera_view;
    mat4 camera_projection;
};

void main()
{
    viewPos = vec3(camera_position);
    FragPos = vec3(model_matrix * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model_matrix))) * aNormal;
    
    gl_Position = camera_projection * camera_view * vec4(FragPos, 1.0);
}
