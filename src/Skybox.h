#pragma once

#include <gl3w/GL/gl3w.h>
#include <gl3w/GL/glcorearb.h>
#include "ShaderHandler.h"

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

namespace skybox_constants {
    static const GLuint NUM_VERTICES = 36;
    static const float VERTICES[NUM_VERTICES * 3] = {
        // https://learnopengl.com/code_viewer.php?code=advanced/cubemaps_skybox_data
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
}

class Skybox {
public:
    Skybox(const std::vector<std::string> & filenames, const std::shared_ptr<ShaderHandler> & shader_handler);
    void draw(const glm::mat4 & projection, const glm::mat4 & view) const;

private:
    void initBuffers();
    void initTextures();

    // void bind(GLenum texture_unit) const;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

    std::vector<std::string> m_filenames;
    std::shared_ptr<ShaderHandler> m_shader_handler;
    GLuint m_tex;
};

