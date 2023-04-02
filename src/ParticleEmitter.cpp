#include "ParticleEmitter.h"

#include <gl3w/GL/gl3w.h>
#include "GL/glcorearb.h"
#include "cs488-framework/GlErrorCheck.hpp"

using namespace particle_constants;

ParticleEmitter::ParticleEmitter(unsigned int num_particles) : m_num_particles(num_particles) {
    m_shader_handler = std::make_unique<ShaderHandler>(
        "./assets/shaders/particle.vs",
        "./assets/shaders/particle.fs"
    );
    m_texture = std::make_unique<Texture>("./assets/textures/fire.png");

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, NUM_VERTICES * sizeof(glm::vec4), &QUAD[0], GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CHECK_GL_ERRORS;

    for (size_t i = 0; i < m_num_particles; ++i) {
        m_particles.emplace_back();
    }
}

void ParticleEmitter::draw(const glm::mat4 & projection) const {
    m_shader_handler->enable();
    m_shader_handler->uploadMat4Uniform("projection", projection);

    m_texture->bind(GL_TEXTURE0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for (const auto & particle : m_particles) {
        if (particle.life <= 0.0f) {
            continue;
        }

        m_shader_handler->uploadVec4Uniform("color", particle.color);
        m_shader_handler->uploadVec3Uniform("offset", particle.pos);

        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleEmitter::tick(float delta_time, const glm::vec3 & position, const glm::vec3 & direction, unsigned int new_particles) {
    for (size_t i = 0; i < new_particles; ++i) {
        const size_t dead_idx = findFirstDeadParticle();
        Particle & particle = m_particles[dead_idx];

        const double random_color = 0.5 + m_rng();
        const double rand = (m_rng() - 0.5) * 10.0;
        particle.life = 1.0f;
        // particle.pos = position + offset + glm::vec3(rand, rand, rand);
        particle.pos = position + glm::vec3(rand, rand, rand);
        particle.color = glm::vec4(random_color, random_color, random_color, 1.0f);
        particle.velocity = direction * 0.1f;
    }

    for (auto & particle : m_particles) {
        particle.life -= delta_time;
        if (particle.life > 0.0f) {
            particle.pos -= particle.velocity * delta_time;
            particle.color.a -= 2.5f * delta_time;
        }
    }
}

size_t ParticleEmitter::findFirstDeadParticle() const {
    for (size_t i = 0; i < m_particles.size(); ++i) {
        if (m_particles[i].life <= 0.0f) {
            return i;
        }
    }

    return 0;
}

