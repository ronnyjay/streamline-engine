#version 330 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 color;

out vec2 TexCoords;
out vec3 Color;

void main()
{
    gl_Position = vec4(vertex, 0, 1);
    TexCoords = uv;
    Color = color;
}
