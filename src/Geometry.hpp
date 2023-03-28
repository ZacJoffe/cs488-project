#pragma once

#include "cs488-framework/OpenGLImport.hpp"
#include "ShaderHandler.hpp"

#include <memory>

class Geometry {
public:
    virtual ~Geometry();

    virtual void draw(const std::shared_ptr<ShaderHandler> & shader_handler) = 0;

private:
    virtual void init() = 0;

    GLuint m_vao;
    GLuint m_vbo;
}
