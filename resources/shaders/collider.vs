#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform bool colliding;

out vec4 VertexColor;

void main() 
{
    gl_Position = projection * view * vec4(aPos, 1.0);
    
    if (colliding) 
    {
        VertexColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else 
    {
        VertexColor = vec4(0.5, 1.0, 0.0, 1.0);
    }
}