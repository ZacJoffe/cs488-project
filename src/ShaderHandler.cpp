#include "ShaderHandler.hpp"

ShaderHandler::ShaderHandler() {}

GLint ShaderHandler::getPositionAttribute() const {
    return m_shader.getAttribLocation("position");
}

void ShaderHandler::enable() {
    m_shader.enable();
}

void ShaderHandler::disable() {
    m_shader.disable();
}

/*
void ShaderHandler::uploadSceneUniforms(const SceneUniformValues & vals) {
    enable();
    {
        if (vals.projection) {
            glUniformMatrix4fv(m_projection_uni, 1, GL_FALSE, glm::value_ptr(vals->projection));
        }

        if (vals.view) {
            glUniformMatrix4fv(m_view_uni, 1, GL_FALSE, glm::value_ptr(vals->view));
        }

        if (vals.model) {
            glUniformMatrix4fv(m_model_uni, 1, GL_FALSE, glm::value_ptr(vals->model));
        }

        if (vals.color) {
            glUniform3f(m_color_uni, vals->color.r, vals->color.g, vals->color.b);
        }
    }
    disable();
}
*/

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

ShaderHandler::ShaderHandler() {
    // build shaders
    m_shader.generateProgramObject();
    m_shader.attachVertexShader(getAssetFilePath("VertexShader.vs").c_str());
    m_shader.attachFragmentShader(getAssetFilePath("FragmentShader.fs").c_str());
    m_shader.link();

    m_projection_uni = m_shader.getUniformLocation("projection");
    m_view_uni = m_shader.getUniformLocation("view");
    m_model_uni = m_shader.getUniformLocation("model");
    m_color_uni = m_shader.getUniformLocation("color");
}
