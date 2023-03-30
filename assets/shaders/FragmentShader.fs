#version 330

out vec4 fragColor;

in vec2 tex_coords;

uniform sampler2D tex;

void main() {
    fragColor = texture(tex, tex_coords);
}
