#pragma once

#include "cs488-framework/OpenGLImport.hpp"

class Geometry {
public:
    virtual ~Geometry() {}

    virtual void draw() = 0;

protected:
    virtual void init() = 0;

    GLuint m_vao;
    GLuint m_vbo;
};

