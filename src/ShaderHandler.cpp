#include "ShaderHandler.h"

#include <glm/gtc/type_ptr.hpp>

ShaderHandler::ShaderHandler() {
    init();
}

ShaderHandler::~ShaderHandler() {
    disable();
}

void ShaderHandler::init() {
    // build shaders
    m_shader.generateProgramObject();
    m_shader.attachVertexShader("./assets/VertexShader.vs");
    m_shader.attachFragmentShader("./assets/FragmentShader.fs");
    m_shader.link();

    m_projection_uni = m_shader.getUniformLocation("projection");
    m_view_uni = m_shader.getUniformLocation("view");
    m_model_uni = m_shader.getUniformLocation("model");
    m_color_uni = m_shader.getUniformLocation("color");

    enable();
}

GLint ShaderHandler::getPositionAttribute() const {
    return m_shader.getAttribLocation("position");
}

void ShaderHandler::enable() {
    m_shader.enable();
}

void ShaderHandler::disable() {
    m_shader.disable();
}

void ShaderHandler::uploadProjectionUniform(const glm::mat4 & projection) {
    glUniformMatrix4fv(m_projection_uni, 1, GL_FALSE, glm::value_ptr(projection));
}

void ShaderHandler::uploadViewUniform(const glm::mat4 & view) {
    glUniformMatrix4fv(m_view_uni, 1, GL_FALSE, glm::value_ptr(view));
}

void ShaderHandler::uploadModelUniform(const glm::mat4 & model) {
    glUniformMatrix4fv(m_model_uni, 1, GL_FALSE, glm::value_ptr(model));
}

void ShaderHandler::uploadColorUniform(const glm::vec3 & color) {
    glUniform3f(m_color_uni, color.r, color.g, color.b);
}

