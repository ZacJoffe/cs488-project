#pragma once

#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"

#include <glm/glm.hpp>
#include <optional>

/*
struct SceneUniformValues {
    std::optional<glm::mat4> projection;
    std::optional<glm::mat4> view;
    std::optional<glm::mat4> model;
    std::optional<glm::vec3> color;
};
*/

// composition-based wrapper of the ShaderProgram class
class ShaderHandler {
public:
    ShaderHandler();

    GLint getPositionAttribute() const;

    void enable();
    void disable();

    // something like this is called A3::appLogic (every frame), not sure if I need it here
    // void uploadSceneUniforms(const SceneUniformValues & vals);

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
