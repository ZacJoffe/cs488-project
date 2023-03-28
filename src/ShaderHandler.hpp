#pragma once

#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"

#include <glm/glm.hpp>

// composition-based wrapper of the ShaderProgram class
class ShaderHandler {
public:
    ShaderHandler();

    GLint getPositionAttribute() const;

    void enable();
    void disable();

    void uploadProjectionUniform(const glm::mat4 & projection);
    void uploadViewUniform(const glm::mat4 & view);
    void uploadModelUniform(const glm::mat4 & model);
    void uploadColorUniform(const glm::vec3 & color);

private:
    ShaderProgram m_shader;

    GLint m_projection_uni;
    GLint m_view_uni;
    GLint m_model_uni;
    GLint m_color_uni;
};
