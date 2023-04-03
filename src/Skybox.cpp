#include "Skybox.h"

#include <gl3w/GL/gl3w.h>
#include <gl3w/GL/glcorearb.h>
#include "cs488-framework/GlErrorCheck.hpp"
#include "ImageLoader.h"

#include <stdexcept>

using namespace skybox_constants;

Skybox::Skybox(const std::vector<std::string> & filenames, const std::shared_ptr<ShaderHandler> & shader_handler) :
    m_filenames(filenames), m_shader_handler(shader_handler)
{
    initBuffers();
    initTextures();
}

void Skybox::draw(const glm::mat4 & projection, const glm::mat4 & view) const {
    GLint old_cull_face_mode;
    glGetIntegerv(GL_CULL_FACE_MODE, &old_cull_face_mode);
    GLint old_depth_func_mode;
    glGetIntegerv(GL_DEPTH_FUNC, &old_depth_func_mode);

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);

    m_shader_handler->enable();
    m_shader_handler->uploadMat4Uniform("projection", projection);

    const glm::mat4 view_stripped = glm::mat4(glm::mat3(view));
    m_shader_handler->uploadMat4Uniform("view", view_stripped);

    glBindVertexArray(m_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_tex);
    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);

    glCullFace(old_cull_face_mode);
    glDepthFunc(old_depth_func_mode);
}

void Skybox::initBuffers() {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CHECK_GL_ERRORS;
}

void Skybox::initTextures() {
    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_tex);

    int x, y, n;
    ImageLoader & image_loader = ImageLoader::getInstance();
    image_loader.setFlipVertically(false);
    for (size_t i = 0; i < m_filenames.size(); ++i) {
        unsigned char * data = image_loader.load(m_filenames[i], &x, &y, &n);
        if (data == nullptr) {
            throw std::runtime_error("Unable to load texture");
        }

        if (n == 3) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (n == 4) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            throw std::runtime_error(&"Unexpected number of components per pixel: " [ n]);
        }

        image_loader.free(data);
    }
    image_loader.setFlipVertically(true);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

