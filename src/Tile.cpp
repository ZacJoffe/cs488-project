#include "Tile.h"
#include "GL/gl3w.h"
#include "GL/glcorearb.h"
#include "cs488-framework/GlErrorCheck.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>

#include <stdexcept>

Tile::Tile(const std::shared_ptr<ShaderHandler> & shader_handler) : m_shader_handler(shader_handler) {
    if (m_shader_handler == nullptr) {
        throw std::runtime_error("Shader handler must not be null");
    }

    init();
}

Tile::~Tile() {}

void Tile::draw() {
    m_texture->bind(GL_TEXTURE0);
    glBindVertexArray(m_vao);

    glm::mat4 world = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.5f));

    for (unsigned int x = 0; x < 10; ++x) {
        for (unsigned int z = 0; z < 10; ++z) {
            glm::mat4 trans = glm::translate(world, glm::vec3(x * 2.0f, 0.0f, z * 2.0f));
            m_shader_handler->uploadModelUniform(trans);
            glDrawElements(GL_TRIANGLES, tile_constants::NUM_INDEXES, GL_UNSIGNED_INT, 0);
        }
    }
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

    // GLint position_attribute = m_shader_handler->getPositionAttribute();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    m_texture = std::make_unique<Texture>("./assets/textures/Grass_02.png");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CHECK_GL_ERRORS;
}

