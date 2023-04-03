#version 330

uniform mat4 light_space;
uniform mat4 model;

layout (location = 0) in vec3 in_position;

void main() {
    gl_Position = light_space * model * vec4(in_position, 1.0);
}

