#pragma once

#include "cs488-framework/ShaderProgram.hpp"
#include <glm/glm.hpp>

// composition-based wrapper of the ShaderProgram class
class ShaderHandler {
public:
    ShaderHandler(const std::string & vertex_filename, const std::string & fragment_filename);
    ~ShaderHandler();

    void enable();
    void disable();

    void uploadMat4Uniform(const std::string & name, const glm::mat4 & m) const;
    void uploadVec3Uniform(const std::string & name, const glm::vec3 & v) const;

private:
    ShaderProgram m_shader;
};
