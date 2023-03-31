#pragma once

#include "Geometry.h"
#include "Texture.h"
#include "ShaderHandler.h"

#include <memory>

namespace tile_constants {
    static const GLuint NUM_VERTICES = 4;

    // this tile covers the entire plane
    static const float VERTICES[NUM_VERTICES * 5] = {
        // x     y      z       texture coords
        -1.0f, -1.0f,  1.0f,    0.0f, 0.0f,  // front left
        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f,  // back left
         1.0f, -1.0f, -1.0f,    1.0f, 1.0f,  // back right
         1.0f, -1.0f,  1.0f,    1.0f, 0.0f   // front right
    };

    static const GLuint NUM_INDEXES = 6;
    static const GLuint VERTICES_INDEXES[NUM_INDEXES] = {
        0, 1, 2,
        2, 3, 0,
    };
}

class Tile : public Geometry {
public:
    Tile(const std::shared_ptr<ShaderHandler> & shader_handler);
    ~Tile() override;

    void draw() override;

private:
    void init() override;

    std::shared_ptr<ShaderHandler> m_shader_handler;
    std::unique_ptr<Texture> m_texture;
};

