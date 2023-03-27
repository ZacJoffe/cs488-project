#include "Floor.hpp"

Floor::Floor() {
    init();
}

Floor::~Floor() {}

void Floor:draw(GLint color_uni) {
    glBindVertexArray(m_vao);
    glUniform3f(color_uni, 1.0f, 1.0f, 1.0f); // TODO change to texture
    glDrawArrays(GL_LINES, 0, floor_constants::NUM_VERTICES);
}

void Floor::init() {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor_constants::VERTICES), floor_constants::VERTICES, GL_STATIC_DRAW);
}
