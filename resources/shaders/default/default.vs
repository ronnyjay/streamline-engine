#version 430 core

layout(location = 0) in vec3 vertices;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertex_color;

out vec3 FragPos;
out vec3 Normal;

void main(){
  gl_Position = projection * view * model * vec4(vertices, 1);

  vertex_color = color;
  FragPos = vec3(model * vec4(vertices, 1.0));
  Normal = mat3(transpose(inverse(model))) * normal;
}