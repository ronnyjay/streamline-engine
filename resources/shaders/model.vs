#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

#define MAX_NUM_LIGHTS 10

struct Light
{
    vec4 pos;
    vec4 color;
};

layout (std140) uniform LightBlock {
    Light lights[MAX_NUM_LIGHTS];
};

uniform uint NumLights;

out vec4 LightPos;
out vec4 LightColor;

out vec2 TexCoords;
out vec3 Normal;   
out vec3 FragPos; 

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoords = aTexCoords;
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    FragPos = vec3(model * vec4(aPos, 1.0));  

    LightColor = vec4(1.0, 1.0, 1.0, 1.0);

    for (int i = 0; i < 1; i++)
    {
        LightColor *= lights[i].color;
    }

    LightPos = vec4(1.0, 1.0, 1.0, 1.0);
}
