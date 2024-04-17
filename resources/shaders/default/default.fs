#version 430 core

in vec3 FragPos;
in vec3 vertex_color;
in vec3 Normal;

uniform vec3 lightPos;

out vec4 FragColor;

void main()
{
    vec3 lightColor = vec3(1, 0.2, 0.2);
    vec3 ambient = vec3(0.1, 0.1, 0.1);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * vertex_color;
    FragColor = vec4(result, 1.0);
}