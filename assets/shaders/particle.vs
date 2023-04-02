#version 330

uniform mat4 projection;
uniform vec4 color;
uniform vec3 offset;

layout (location = 0) in vec4 in_vertex;

out vec2 tex_coords;
out vec4 particle_color;

void main() {
    float scale = 10.0f;
    tex_coords = vertex.zw;
    particle_color = color;
    gl_Position = projection * vec4((vertex.xy * scale) + offset, 0.0, 1.0);
}
