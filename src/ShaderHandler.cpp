#include "ShaderHandler.h"

#include <glm/gtc/type_ptr.hpp>

ShaderHandler::ShaderHandler(const std::string & vertex_filename, const std::string & fragment_filename) {
    // build shaders
    m_shader.generateProgramObject();
    m_shader.attachVertexShader(vertex_filename.c_str());
    m_shader.attachFragmentShader(fragment_filename.c_str());
    m_shader.link();
    enable();
}

ShaderHandler::~ShaderHandler() {
    disable();
}

void ShaderHandler::enable() {
    m_shader.enable();
}

void ShaderHandler::disable() {
    m_shader.disable();
}

void ShaderHandler::uploadMat4Uniform(const std::string & name, const glm::mat4 & m) const {
    GLint uni = m_shader.getUniformLocation(name.c_str());
    glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderHandler::uploadVec2Uniform(const std::string & name, const glm::vec2 & v) const {
    GLint uni = m_shader.getUniformLocation(name.c_str());
    glUniform2f(uni, v.x, v.y);
}

void ShaderHandler::uploadVec3Uniform(const std::string & name, const glm::vec3 & v) const {
    GLint uni = m_shader.getUniformLocation(name.c_str());
    glUniform3f(uni, v.x, v.y, v.z);
}

void ShaderHandler::uploadVec4Uniform(const std::string & name, const glm::vec4 & v) const {
    GLint uni = m_shader.getUniformLocation(name.c_str());
    glUniform4f(uni, v.x, v.y, v.z, v.w);
}
