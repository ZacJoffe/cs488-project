#version 330

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_tex_coords;

out vec2 tex_coords;

void main() {
    gl_Position = projection * view * model * vec4(in_position, 1.0);
    tex_coords = in_tex_coords;
}
