#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

void main() {
    gl_Position = projection * view * model * vec4(vertex, 1);
    FragPos = vec3(model * vec4(vertex, 1.0));
    TexCoord = uv;
    Normal = normal;
}
