#version 330

uniform mat4 projection;
uniform vec4 color;
uniform vec3 offset;

layout (location = 0) in vec3 in_vertex;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_tex_coords;

out vec2 tex_coords;
out vec4 particle_color;

void main() {
    float scale = 10.0f;
    tex_coords = in_tex_coords;
    particle_color = color;
    gl_Position = projection * vec4((in_vertex * scale) + offset, 1.0);
}
