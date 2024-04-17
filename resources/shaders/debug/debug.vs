#version 330 core
layout (location = 0) in vec3 vertices;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec2 TexCoords;

void main() {
    gl_Position = projection * view * model * vec4(vertices, 1);

    TexCoords = aTexCoord; // Assume these are normalized [0,1] across the object
}
