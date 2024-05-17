#version 330 core

layout(location = 0) in vec3 aPos;

out vec4 vertexColor;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform bool collision;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    if (collision) {
        vertexColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else {
        vertexColor = vec4(1.0, 0.9, 0.0, 1.0);
    }
}