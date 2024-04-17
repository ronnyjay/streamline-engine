#version 330 core
out vec4 FragColor;
in vec2 TexCoords;


void main() {
    vec2 scaledTexCoords = TexCoords * 10.0;
    vec2 checkPosition = floor(scaledTexCoords);
    float checker = mod(checkPosition.x + checkPosition.y, 2.0);
    vec3 color = checker < 1.0 ? vec3(0.0, 0.0, 0.0) : vec3(0.5, 0.0, 0.5); 
    FragColor = vec4(color, 1.0);
}
