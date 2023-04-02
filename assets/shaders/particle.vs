#version 330

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec4 color;

layout (location = 0) in vec3 in_vertex;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_tex_coords;

out vec2 tex_coords;
out vec4 particle_color;

void main() {
    float scale = 0.005f;
    tex_coords = in_tex_coords;
    particle_color = color;

    // billboarding (make particle meshes always face camera)
    // https://www.reddit.com/r/opengl/comments/bi7fc8/glsl_rotating_a_billboards_xaxis_towards_camera/em0p3mk/
    mat4 mv = view * model;
    mv[0].xzy = vec3(1, 0, 0);
    mv[1].xzy = vec3(0, 1, 0);
    mv[2].xzy = vec3(0, 0, 1);

    gl_Position = projection * mv * vec4((in_vertex * scale), 1.0);
}
