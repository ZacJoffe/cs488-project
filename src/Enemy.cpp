#include "Enemy.h"

#include <gl3w/GL/gl3w.h>
#include "cs488-framework/ObjFileDecoder.hpp"
#include "cs488-framework/GlErrorCheck.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/constants.hpp"
#include <glm/gtx/string_cast.hpp>

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace enemy_constants;

unsigned int Enemy::s_enemy_count = 0;

Enemy::Enemy(const std::shared_ptr<ShaderHandler> & shader_handler,
             const glm::vec3 & pos,
             const std::shared_ptr<Texture> & texture,
             const std::string & mesh_filename) :
    m_shader_handler(shader_handler), m_pos(pos), m_texture(texture), m_alive(true), m_ticks(0)
{
    m_id = "enemy" + std::to_string(s_enemy_count);
    ++s_enemy_count;

    std::string obj_name = ""; // unused
    ObjFileDecoder::decode(mesh_filename.c_str(), obj_name, m_positions, m_normals, m_uv_coords);
    initBuffers();

    m_bounding_box_xz = updateBoundingBoxHelper(m_pos);
    m_move_direction = getRandomDirection();

    m_particle_emitter = std::make_unique<ParticleEmitter>(1000);
    std::cout << "created enemy: " << m_id << std::endl;
}

void Enemy::draw(const glm::mat4 & projection, const glm::mat4 & view) const {
    m_shader_handler->enable();
    m_texture->bind(GL_TEXTURE0);

    glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_pos);
    m_shader_handler->uploadMat4Uniform("model", trans);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_positions.size());

    m_particle_emitter->draw(projection, view);

    m_shader_handler->disable();
}

bool Enemy::collisionTestXZ(const Ray & ray) const {
    const auto line_segments = m_bounding_box_xz.getLineSegments();
    return ray.collisionTestXZ(line_segments);
}

void Enemy::kill() {
    if (m_alive) {
        std::cout << "killing enemy " + m_id << std::endl;
        m_pos += glm::vec3(0.0f, -1.0f, 0.0f);
        m_particle_emitter->emit(m_pos + glm::vec3(0.0f, -1.0f, 0.0f));

        m_alive = false;
    } else {
        m_particle_emitter->emit(m_pos + glm::vec3(0.0f, -1.0f, 0.0f));
    }
}

void Enemy::move(const std::list<BoundingBox> & collidable_objects, float delta_time) {
    m_particle_emitter->tick(delta_time, m_pos + glm::vec3(0.0f, -1.0f, 0.0f), 2);
    if (!m_alive) {
        return;
    }

    // get new random direction vector every MAX_TICKS ticks
    if (m_ticks == MAX_TICKS) {
        m_ticks = 0;
        m_move_direction = getRandomDirection();
    }

    const float speed = SPEED * delta_time;
    while (!tryUpdatePosition(speed * m_move_direction, collidable_objects)) {
        // if we fail to update our position due to a collision, get another
        // direction vector and try again
        m_move_direction = getRandomDirection();
    }

    ++m_ticks;
}

std::string Enemy::getId() const {
    return m_id;
}

BoundingBox Enemy::getBoundingBox() const {
    return m_bounding_box_xz;
}

void Enemy::initBuffers() {
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

BoundingBox Enemy::updateBoundingBoxHelper(const glm::vec3 & pos) const {
    return BoundingBox(
        glm::vec2(pos.x - BOUNDING_BOX_OFFSET, pos.z - BOUNDING_BOX_OFFSET),
        glm::vec2(pos.x + BOUNDING_BOX_OFFSET, pos.z + BOUNDING_BOX_OFFSET)
    );
}

void Enemy::updateBoundingBoxXZ() {
    m_bounding_box_xz = updateBoundingBoxHelper(m_pos);
}

glm::vec3 Enemy::getRandomDirection() const {
    const double x = m_rng() * 2.0 * glm::pi<double>();
    return glm::normalize(
        glm::vec3(
            glm::sin(x),
            0.0f,
            glm::cos(x)
        )
    );
}

bool Enemy::tryUpdatePosition(const glm::vec3 & velocity, std::list<BoundingBox> collidable_objects) {
    const glm::vec3 new_pos = m_pos + velocity;
    const BoundingBox new_bounding_box = updateBoundingBoxHelper(new_pos);

    for (const auto & obj : collidable_objects) {
        if (new_bounding_box.collisionTest(obj)) {
            return false;
        }
    }

    m_pos = new_pos;
    m_bounding_box_xz = new_bounding_box;
    return true;
}


