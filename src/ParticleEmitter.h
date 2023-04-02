#pragma once

#include "Rng.h"
#include "ShaderHandler.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace particle_constants {
    static const unsigned int NUM_VERTICES = 6;
    static const glm::vec4 QUAD[NUM_VERTICES] = {
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)
    };
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
    size_t findFirstDeadParticle() const;

    GLuint m_vao;
    GLuint m_vbo;

    std::vector<Particle> m_particles;

    std::unique_ptr<ShaderHandler> m_shader_handler;
    std::unique_ptr<Texture> m_texture;
    unsigned int m_num_particles;
    Rng m_rng;
};

