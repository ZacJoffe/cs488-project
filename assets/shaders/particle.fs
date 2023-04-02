#version 330

in vec2 tex_coords;
in vec4 particle_color;

out vec4 color;

uniform sampler2D tex;

void main() {
    color = texture(tex, tex_coords) * particle_color;
}
