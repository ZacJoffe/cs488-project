#pragma once

#include <gl3w/GL/gl3w.h>
#include <gl3w/GL/glcorearb.h>
#include <glm/glm.hpp>

#include <string>

class ShaderHandler {
public:
    ShaderHandler(const std::string & vertex_filename, const std::string & fragment_filename);
    ~ShaderHandler();

    void enable();
    void disable();

    void uploadMat4Uniform(const std::string & name, const glm::mat4 & m) const;
    void uploadVec2Uniform(const std::string & name, const glm::vec2 & v) const;
    void uploadVec3Uniform(const std::string & name, const glm::vec3 & v) const;
    void uploadVec4Uniform(const std::string & name, const glm::vec4 & v) const;

private:
    struct Shader {
        GLuint shader_object;
        std::string filepath;

        Shader() : shader_object(0), filepath() {}
    };

    void extractSourceAndCompile(const Shader & shader);
    GLint getUniformLocation(const std::string & name) const;

    Shader m_vertex_shader;
    Shader m_fragment_shader;

    GLuint m_program_object;
};

