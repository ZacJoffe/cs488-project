#include "ParticleEmitter.h"

#include <gl3w/GL/gl3w.h>
#include <gl3w/GL/glcorearb.h>
#include "cs488-framework/GlErrorCheck.hpp"
#include "cs488-framework/ObjFileDecoder.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

using namespace particle_constants;

ParticleEmitter::ParticleEmitter(unsigned int num_particles) : m_num_particles(num_particles) {
    m_shader_handler = std::make_unique<ShaderHandler>(
        "./assets/shaders/particle.vs",
        "./assets/shaders/particle.fs"
    );
    m_texture = std::make_unique<Texture>("./assets/textures/fire.png");

    std::string id = "particle_cube";
    ObjFileDecoder::decode("./assets/meshes/cube.obj", id, m_positions, m_normals, m_uv_coords);
    initBuffers();

    for (size_t i = 0; i < m_num_particles; ++i) {
        m_particles.emplace_back();
    }
}

void ParticleEmitter::draw(const glm::mat4 & projection, const glm::mat4 & view) const {
    m_shader_handler->enable();
    m_shader_handler->uploadMat4Uniform("projection", projection);
    m_shader_handler->uploadMat4Uniform("view", view);

    m_texture->bind(GL_TEXTURE0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for (const auto & particle : m_particles) {
        if (particle.life <= 0.0f) {
            continue;
        }

        m_shader_handler->uploadVec4Uniform("color", particle.color);

        glm::mat4 trans = glm::translate(glm::mat4(1.0f), particle.pos);
        m_shader_handler->uploadMat4Uniform("model", trans);

        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, m_positions.size());
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleEmitter::tick(float delta_time,
                           const glm::vec3 & position,
                           const glm::vec3 & direction,
                           unsigned int new_particles)
{
    for (size_t i = 0; i < new_particles; ++i) {
        const size_t dead_idx = findFirstDeadParticle();
        Particle & particle = m_particles[dead_idx];

        const double random_color = 0.5 + m_rng();
        const double rand = (m_rng() - 0.5) * 0.1f;
        particle.life = 1.0f;
        particle.pos = position + glm::normalize(glm::vec3(m_rng(), m_rng(), m_rng())) * 0.1f;
        particle.color = glm::vec4(random_color, random_color, random_color, 1.0f);
        particle.velocity = glm::normalize(glm::vec3(m_rng(), m_rng(), m_rng())) * 0.1f;
    }

    for (auto & particle : m_particles) {
        particle.life -= delta_time;

        // update position of particle to follow camera
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), position - m_prev_pos);
        particle.pos = glm::vec3(trans * glm::vec4(particle.pos, 1.0f));

        if (particle.life > 0.0f) {
            particle.pos -= particle.velocity * delta_time;
            particle.color.a -= 2.5f * delta_time;
        }
    }

    m_prev_pos = position;
}

void ParticleEmitter::initBuffers() {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, m_positions.size() * sizeof(glm::vec3), &m_positions[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_vbo_normals);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normals);
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &m_vbo_uvs);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uvs);
    glBufferData(GL_ARRAY_BUFFER, m_uv_coords.size() * sizeof(glm::vec2), &m_uv_coords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CHECK_GL_ERRORS;
}

size_t ParticleEmitter::findFirstDeadParticle() const {
    for (size_t i = 0; i < m_particles.size(); ++i) {
        if (m_particles[i].life <= 0.0f) {
            return i;
        }
    }

    return 0;
}

