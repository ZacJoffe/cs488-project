#pragma once

#include "cs488-framework/OpenGLImport.hpp"

#include <glm/glm.hpp>

class Geometry {
public:
    virtual ~Geometry() {}

    virtual void draw() = 0;

protected:
    virtual void init() = 0;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

    glm::mat4 m_trans;
};

