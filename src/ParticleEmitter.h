#pragma once

#include "Rng.h"
#include "ShaderHandler.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace particle_constants {
    static const float DEFAULT_LIFE = 1.0f;
}

struct Particle {
    glm::vec3 pos;
    glm::vec3 velocity;
    glm::vec4 color;
    float life;
    unsigned int lives;
    Particle() : pos(0.0f), velocity(0.0f), color(1.0f), life(0.0f), lives(0) {}
};

class ParticleEmitter {
public:
    ParticleEmitter(unsigned int num_particles);

    void emit(unsigned int lives, const glm::vec3 & position);
    void draw(const glm::mat4 & projection, const glm::mat4 & view) const;
    void tick(float delta_time,
              const glm::vec3 & position,
              unsigned int new_particles);

private:
    void initBuffers();
    void initParticle(Particle & particle, const glm::vec3 & position);
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

    glm::vec3 m_prev_pos;

    Rng m_rng;
};

