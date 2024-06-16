#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D TexDiffuse1;
uniform sampler2D TexNormal1;
uniform sampler2D TexSpecular1;
uniform sampler2D TexAmbient1;

uniform vec3 viewPos;

struct LightProperties
{
    vec4 color;
};

struct Light
{
    vec4 pos;
    LightProperties properties;
};

#define MAX_NUM_LIGHTS 10

uniform uint NumLights;

layout (std140) uniform LightBlock {
    Light lights[MAX_NUM_LIGHTS];
};

void main() {
    vec4 ObjectColor = texture(TexDiffuse1, TexCoords);
    vec4 SpecularEffect = texture(TexSpecular1, TexCoords);
    vec4 NormalEffect = texture(TexNormal1, TexCoords);
    vec4 AmbientEffect = texture(TexAmbient1, TexCoords) * 0.1;

    vec3 norm = normalize(Normal * NormalEffect.xyz);

    vec4 lightColor = vec4(0.0, 0.0, 0.0, 1.0);

    vec3 viewDir = normalize(viewPos - FragPos);

    for (uint i = 0u; i < NumLights; i++)
    {
        vec3 lightToFrag = lights[i].pos.xyz - FragPos;
        vec3 lightDir = normalize(lightToFrag);
        float distanceToLight = length(lightToFrag);
        float intensity = 1 / pow(distanceToLight * distanceToLight, 0.1);

        float diff = max(dot(norm, lightDir), 0.0);

        vec3 diffuse = diff * (lights[i].properties.color.rgb + ObjectColor.rgb) * intensity;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);  // Shininess factor
        vec4 specular = (spec * lights[i].properties.color * intensity) * SpecularEffect;

        lightColor += vec4(diffuse, 1.0) + specular;
    }

    lightColor += AmbientEffect;

    FragColor = lightColor;
    // FragColor = ObjectColor;
}
