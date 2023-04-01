#pragma once

#include <gl3w/GL/gl3w.h>

#include "BoundingBox.h"
#include "Ray.h"
#include "ShaderHandler.h"

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

namespace enemy_constants {
    static const float BOUNDING_BOX_OFFSET = 0.5f;
}

class Enemy {
public:
    Enemy(const std::shared_ptr<ShaderHandler> & shader_handler, const glm::vec3 & pos, const std::string & mesh_filename);

    void draw(const glm::mat4 & world_trans = glm::mat4(1.0f)) const;
    bool collisionTestXZ(const Ray & ray) const;
    void kill();
    std::string getId() const;

private:
    void initBuffers();
    BoundingBox updateBoundingBoxHelper(const glm::vec3 & pos) const;
    void updateBoundingBoxXZ();

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
    // TODO movement with (very basic) ai and static collision detection
};

