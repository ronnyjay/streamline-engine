#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 translation;

void main() 
{
    gl_Position = projection * view * vec4(aPos + translation, 1.0);
}