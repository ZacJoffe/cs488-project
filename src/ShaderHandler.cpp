#include "ShaderHandler.h"
#include "cs488-framework/GlErrorCheck.hpp" // TODO

#include <cstdio>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <stdexcept>

ShaderHandler::ShaderHandler(const std::string & vertex_filename, const std::string & fragment_filename) :
    m_program_object(0)
{
    m_program_object = glCreateProgram();

    const auto createShader = [](GLenum shader_type) {
        GLuint id = glCreateShader(shader_type);
        CHECK_GL_ERRORS;
        return id;
    };

    m_vertex_shader.shader_object = createShader(GL_VERTEX_SHADER);
    m_vertex_shader.filepath = vertex_filename;
    extractSourceAndCompile(m_vertex_shader);

    m_fragment_shader.shader_object = createShader(GL_FRAGMENT_SHADER);
    m_fragment_shader.filepath = fragment_filename;
    extractSourceAndCompile(m_fragment_shader);

    glAttachShader(m_program_object, m_vertex_shader.shader_object);
    glAttachShader(m_program_object, m_fragment_shader.shader_object);
    glLinkProgram(m_program_object);

    GLint link_success;
    glGetProgramiv(m_program_object, GL_LINK_STATUS, &link_success);
    if (link_success == GL_FALSE) {
        // Get the length in chars of the link error message.
        GLint err_msg_length;
        glGetProgramiv(m_program_object, GL_INFO_LOG_LENGTH, &err_msg_length);

        // Retrieve the link error message.
        GLchar err_msg[err_msg_length];
        glGetProgramInfoLog(m_program_object, err_msg_length, NULL, err_msg);

        std::stringstream err;
        err << "Error linking shaders: " << err_msg << std::endl;
        throw std::runtime_error(err.str());
    }
    CHECK_GL_ERRORS;
}

ShaderHandler::~ShaderHandler() {
    disable();
}

void ShaderHandler::enable() {
    glUseProgram(m_program_object);
    CHECK_GL_ERRORS;
}

void ShaderHandler::disable() {
    glUseProgram(static_cast<GLuint>(NULL));
    CHECK_GL_ERRORS;
}

void ShaderHandler::uploadMat4Uniform(const std::string & name, const glm::mat4 & m) const {
    const GLint uni = getUniformLocation(name);
    glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderHandler::uploadVec2Uniform(const std::string & name, const glm::vec2 & v) const {
    const GLint uni = getUniformLocation(name);
    glUniform2f(uni, v.x, v.y);
}

void ShaderHandler::uploadVec3Uniform(const std::string & name, const glm::vec3 & v) const {
    const GLint uni = getUniformLocation(name);
    glUniform3f(uni, v.x, v.y, v.z);
}

void ShaderHandler::uploadVec4Uniform(const std::string & name, const glm::vec4 & v) const {
    const GLint uni = getUniformLocation(name);
    glUniform4f(uni, v.x, v.y, v.z, v.w);
}

void ShaderHandler::extractSourceAndCompile(const Shader & shader) {
    std::ifstream file;
    file.open(shader.filepath.c_str());
    if (!file) {
        std::stringstream err;
        err << "Failed to open file: " << shader.filepath << std::endl;
        throw std::runtime_error(err.str());
    }

    std::stringstream stream;
    std::string line;
    while (file.good()) {
        getline(file, line, '\r');
        stream << line;
    }
    file.close();
    stream << '\0';

    const std::string tmp = stream.str();
    const char * shader_source_code = tmp.c_str();
    glShaderSource(shader.shader_object, 1, static_cast<const GLchar **>(&shader_source_code), nullptr);
    glCompileShader(shader.shader_object);

    GLint compile_success;
    glGetShaderiv(shader.shader_object, GL_COMPILE_STATUS, &compile_success);
    if (compile_success == GL_FALSE) {
        // Get the length in chars of the compilation error message.
        GLint err_msg_length;
        glGetShaderiv(shader.shader_object, GL_INFO_LOG_LENGTH, &err_msg_length);

        // Retrieve the compilation error message.
        GLchar err_msg[err_msg_length + 1]; // Add 1 for null terminator
        glGetShaderInfoLog(shader.shader_object, err_msg_length, NULL, err_msg);

        std::stringstream err;
        err << "Error compiling shader: " << err_msg << std::endl;
        throw std::runtime_error(err.str());
    }
    CHECK_GL_ERRORS;
}

GLint ShaderHandler::getUniformLocation(const std::string & name) const {
    const GLint uni = glGetUniformLocation(m_program_object, static_cast<const GLchar *>(name.c_str()));
    if (uni == -1) {
        std::stringstream err;
        err << "Error obtaining uniform location: " << name << std::endl;
        throw std::runtime_error(err.str());
    }

    return uni;
}

