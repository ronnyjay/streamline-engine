#version 330 core

in vec2 Pos;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D text;
uniform vec3 color;

void main()
{
    vec4 c = texture(text, TexCoords);
    if (c.r < 0.2)
    {
        discard;
    }

    // FragColor = vec4(Color.r, c.r, c.r, 1);
    FragColor = vec4(color.r, color.g, color.b, 1);
}
