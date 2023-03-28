#include "Floor.hpp"

#include <stdexcept>

Floor::Floor() {
    init();
}

Floor::~Floor() {}

void Floor::draw(const std::shared_ptr<ShaderHandler> & shader_handler) {
    if (shader_handler == nullptr) {
        throw std::runtime_error("Shader handler must not be null");
    }

    glBindVertexArray(m_vao);
    shader_handler->uploadColorUniform(glm::vec3(1.0f, 1.0f, 1.0f)); // TODO change to texture
    glDrawArrays(GL_LINES, 0, floor_constants::NUM_VERTICES);
}

void Floor::init() {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor_constants::VERTICES), floor_constants::VERTICES, GL_STATIC_DRAW);
}
