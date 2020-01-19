#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 ViewPos;
out vec3 FragPos;
out vec3 Normal;

struct Camera {
    vec3 position;
    
    mat4 view;
    mat4 projection;
};

uniform Camera camera;
uniform mat4 model_matrix;

void main()
{
    ViewPos = camera.position;
    FragPos = vec3(model_matrix * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model_matrix))) * aNormal;
    
    gl_Position = camera.projection * camera.view * vec4(FragPos, 1.0);
}
