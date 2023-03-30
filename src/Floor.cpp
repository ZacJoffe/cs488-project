#include "Floor.h"
#include "GL/gl3w.h"
#include "GL/glcorearb.h"
#include "cs488-framework/GlErrorCheck.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"

#include <stdexcept>

Floor::Floor(const std::shared_ptr<ShaderHandler> & shader_handler) : m_shader_handler(shader_handler) {
    if (m_shader_handler == nullptr) {
        throw std::runtime_error("Shader handler must not be null");
    }

    init();
}

Floor::~Floor() {}

void Floor::draw() {
    glBindTexture(GL_TEXTURE_2D, m_tex);
    glBindVertexArray(m_vao);

    glm::mat4 trans(1.0f);

    // trans = glm::scale(trans, glm::vec3(10.0f, 1.0f, 10.0f));
    m_shader_handler->uploadModelUniform(trans);
    glDrawElements(GL_TRIANGLES, floor_constants::NUM_INDEXES, GL_UNSIGNED_INT, 0);
}

void Floor::init() {
    using namespace floor_constants;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VERTICES_INDEXES), VERTICES_INDEXES, GL_STATIC_DRAW);

    // GLint position_attribute = m_shader_handler->getPositionAttribute();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    initTexture();

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CHECK_GL_ERRORS;
}

void Floor::initTexture() {
    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int x, y, n;
    unsigned char * data = stbi_load("./assets/textures/Grass_02.png", &x, &y, &n, 0);
    if (data == nullptr) {
        throw std::runtime_error("Unable to load texture");
    }

    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    if (n == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else if (n == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
        throw std::runtime_error(&"Unexpected number of components per pixel: " [ n]);
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

