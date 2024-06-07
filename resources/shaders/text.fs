#version 330 core

in vec2 Pos;
in vec2 TexCoords;
in vec3 Color;

out vec4 color;

out vec4 FragCoord;

uniform sampler2D text;

void main()
{
    vec4 c = texture(text, TexCoords);
    if (c.r < 0.1)
    {
        discard;
    }

    color = vec4(Color * c.r, 1);
}