#version 330

uniform mat4 projection;
uniform mat4 view;

layout (location = 0) in vec3 in_position;

out vec3 tex_coords;

void main() {
    tex_coords = in_position;
    vec4 position = projection * view * vec4(in_position, 1.0);
    gl_Position = position.xyww;
}

