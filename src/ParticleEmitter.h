#pragma once

#include "Rng.h"
#include "ShaderHandler.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace particle_constants {
    /*
    static const GLuint NUM_VERTICES = 8;
    static const float VERTICES[NUM_VERTICES * 3] = {
        // ordering from cube.mesh
        // x    y    z
        0.0f, 0.0f, 1.0f, // bottom-left, front
        0.0f, 1.0f, 1.0f, // top-left, front
        0.0f, 0.0f, 0.0f, // bottom-left, back
        0.0f, 1.0f, 0.0f, // top-left, back

        1.0f, 0.0f, 1.0f, // bottom-right, front
        1.0f, 1.0f, 1.0f, // top-right, front
        1.0f, 0.0f, 0.0f, // bottom-right, back
        1.0f, 1.0f, 0.0f, // top-right, back
    };

    static const GLuint NUM_UV_COORDS = 14;
    static const float UV_COORDS[NUM_UV_COORDS * 2] = {
        // from cube.mesh
        0.375f, 0.0f,
        0.375f, 1.0f,
        0.125f, 0.75f,
        0.625f, 0.0f,
        0.625f, 1.0f,
        0.875f, 0.75f,
        0.125f, 0.5f,
        0.375f, 0.25f,
        0.625f, 0.25f,
        0.875f, 0.5f,
        0.375f, 0.75f,
        0.625f, 0.75f,
        0.375f, 0.5f,
        0.625f, 0.5f
    };

    static const GLuint NUM_INDEXES = 36;
    static const GLuint VERTICES_INDEXES[NUM_INDEXES] = {
        // FIXME
        // front face
        0, 1, 2,
        2, 3, 0,

        // back face
        4, 5, 6,
        6, 7, 4,

        // top face
        4, 5, 1,
        1, 0, 4,

        // bottom face
        7, 6, 2,
        2, 3, 7,

        // right face
        1, 5, 6,
        6, 2, 1,

        // left face
        4, 0, 3,
        3, 7, 4,
    };
    */
}

struct Particle {
    glm::vec3 pos;
    glm::vec3 velocity;
    glm::vec4 color;
    float life;
    Particle() : pos(0.0f), velocity(0.0f), color(1.0f), life(0.0f) {}
};

class ParticleEmitter {
public:
    ParticleEmitter(unsigned int num_particles);

    void draw(const glm::mat4 & projection) const;
    void tick(float delta_time, const glm::vec3 & position, const glm::vec3 & direction, unsigned int new_particles);

private:
    void initBuffers();
    size_t findFirstDeadParticle() const;

    GLuint m_vao;
    GLuint m_vbo_vertices;
    GLuint m_vbo_normals;
    GLuint m_vbo_uvs;

    std::vector<Particle> m_particles;

    // particle mesh data
    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec2> m_uv_coords;

    std::unique_ptr<ShaderHandler> m_shader_handler;
    std::unique_ptr<Texture> m_texture;
    unsigned int m_num_particles;
    Rng m_rng;
};

