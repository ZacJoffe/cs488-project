#include "Tile.h"
#include "GL/gl3w.h"
#include "GL/glcorearb.h"
#include "cs488-framework/GlErrorCheck.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <glm/glm.hpp>
#include <memory>
#include <stdexcept>

Tile::Tile(const std::shared_ptr<ShaderHandler> & shader_handler, const glm::mat4 & trans, const std::shared_ptr<Texture> & texture) :
    m_shader_handler(shader_handler), m_trans(trans), m_texture(texture) {
    if (m_shader_handler == nullptr) {
        throw std::runtime_error("Shader handler must not be null");
    }

    init();
}

void Tile::draw(const glm::mat4 & world_trans) const {
    m_texture->bind(GL_TEXTURE0);
    // m_shader_handler->uploadModelUniform(m_trans * world_trans);
    m_shader_handler->uploadModelUniform(world_trans * m_trans);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, tile_constants::NUM_INDEXES, GL_UNSIGNED_INT, 0);
}

void Tile::init() {
    using namespace tile_constants;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VERTICES_INDEXES), VERTICES_INDEXES, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // m_texture = std::make_unique<Texture>(tex_filename);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CHECK_GL_ERRORS;
}


Tiles::Tiles() {}

Tiles::Tiles(const glm::mat4 & world_trans,
             unsigned int num_x,
             unsigned int num_z,
             const std::shared_ptr<ShaderHandler> & shader_handler,
             const std::shared_ptr<Texture> & texture,
             const std::optional<std::pair<glm::vec2, glm::vec2>> & bounding_box_xy) :
    m_trans(world_trans), m_bounding_box_xy(bounding_box_xy) {
    for (unsigned int x = 0; x < num_x; ++x) {
        for (unsigned int z = 0; z < num_z; ++z) {
            const glm::mat4 tile_trans = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z));
            m_tiles.push_back(std::make_unique<Tile>(shader_handler, tile_trans, texture));
        }
    }
}

void Tiles::draw() const {
    for (const auto & tile : m_tiles) {
        tile->draw(m_trans);
    }
}

