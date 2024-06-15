#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

in vec4 LightPos;
in vec4 LightColor;

uniform sampler2D TexDiffuse1;

void main() {
    // vec4 LightPos = vec4(0.0, 0.0, 0.0, 1.0);
    // vec4 LightColor = vec4(1.0, 0.0, 0.0, 1.0);

    vec4 ObjectColor = texture(TexDiffuse1, TexCoords);
    vec4 AmbientColor = vec4(0.6, 0.6, 0.6, 1.0);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(FragPos - LightPos.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * LightColor;
    FragColor = (diffuse + AmbientColor) * ObjectColor;
    // FragColor = LghtColor;
}
