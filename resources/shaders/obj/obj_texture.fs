#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

in vec2 TexCoord;

uniform sampler2D Tex;

void main() {
    vec3 ObjectColor = texture(Tex, TexCoord);
    vec3 AmbientColor = vec3(0.1, 0.1, 0.1);
    vec3 LightColor = vec3(0.8, 0.3, 0.3);
    vec3 LightPos = vec3(0.0, 0.0, 0.0);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(FragPos - LightPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * LightColor;
    vec3 result = (diffuse + AmbientColor) * ObjectColor;
    FragColor = vec4(result, 1.0);
}
