#include "Floor.h"
#include "cs488-framework/GlErrorCheck.hpp"

#include <stdexcept>

Floor::Floor(const std::shared_ptr<ShaderHandler> & shader_handler) : m_shader_handler(shader_handler) {
    if (m_shader_handler == nullptr) {
        throw std::runtime_error("Shader handler must not be null");
    }

    init();
}

Floor::~Floor() {}

void Floor::draw() {
    glBindVertexArray(m_vao);
    m_shader_handler->uploadColorUniform(glm::vec3(1.0f, 1.0f, 1.0f)); // TODO change to texture
    glDrawElements(GL_TRIANGLES, floor_constants::NUM_INDEXES, GL_UNSIGNED_INT, 0);
}

void Floor::init() {
    using namespace floor_constants;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VERTICES_INDEXES), VERTICES_INDEXES, GL_STATIC_DRAW);

    GLint position_attribute = m_shader_handler->getPositionAttribute();
    glEnableVertexAttribArray(position_attribute);
    glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CHECK_GL_ERRORS;
}
