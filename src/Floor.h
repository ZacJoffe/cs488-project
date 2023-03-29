#pragma once

#include "Geometry.h"
#include "ShaderHandler.h"

#include <memory>

namespace floor_constants {
    static const GLuint NUM_VERTICES = 4;

    // this floor covers the entire plane
    static const float VERTICES[NUM_VERTICES * 3] = {
        // x, y, z, right hand coordinate system
        -1.0f, -1.0f, 1.0f,   // front left
        -1.0f, -1.0f, -1.0f,  // back left
        1.0f, -1.0f, -1.0f,   // back right
        1.0f, -1.0f, 1.0f,    // front right
    };

    static const GLuint NUM_INDEXES = 6;
    static const GLuint VERTICES_INDEXES[NUM_INDEXES] = {
        0, 1, 2,
        2, 3, 0,
    };
}

class Floor : public Geometry {
public:
    Floor(const std::shared_ptr<ShaderHandler> & shader_handler);
    ~Floor() override;

    void draw() override;

private:
    void init() override;

    std::shared_ptr<ShaderHandler> m_shader_handler;
};

