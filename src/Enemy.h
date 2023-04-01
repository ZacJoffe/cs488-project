#pragma once

#include <gl3w/GL/gl3w.h>

#include "BoundingBox.h"
#include "Ray.h"
#include "ShaderHandler.h"

#include <glm/glm.hpp>
#include <memory>
#include <random>
#include <string>
#include <vector>

namespace enemy_constants {
    static const float BOUNDING_BOX_OFFSET = 1.0f;
    static const unsigned int MAX_TICKS = 100;
    static const float SPEED = 5.0f;
}

class Enemy {
public:
    Enemy(const std::shared_ptr<ShaderHandler> & shader_handler, const glm::vec3 & pos, const std::string & mesh_filename);

    void draw(const glm::mat4 & world_trans = glm::mat4(1.0f)) const;
    bool collisionTestXZ(const Ray & ray) const;
    void kill();
    void move(const std::list<BoundingBox> & collidable_objects, float delta_time);

    std::string getId() const;
    BoundingBox getBoundingBox() const;

private:
    void initBuffers();
    BoundingBox updateBoundingBoxHelper(const glm::vec3 & pos) const;
    void updateBoundingBoxXZ();
    glm::vec3 getRandomDirection() const;
    bool tryUpdatePosition(const glm::vec3 & velocity, std::list<BoundingBox> collidable_objects);


    static unsigned int s_enemy_count;

    std::string m_id;
    GLuint m_vao;
    GLuint m_vbo_vertices;
    GLuint m_vbo_normals;
    GLuint m_vbo_uvs;
    // GLuint m_ebo;

    std::shared_ptr<ShaderHandler> m_shader_handler;
    // std::shared_ptr<Texture> m_texture;

    // mesh data
    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec2> m_uv_coords;

    glm::vec3 m_pos;
    BoundingBox m_bounding_box_xz;

    bool m_alive;

    glm::vec3 m_move_direction;
    unsigned int m_ticks;
};

