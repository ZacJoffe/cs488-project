#pragma once

#include "ShaderHandler.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace tile_constants {
    static const GLuint NUM_VERTICES = 4;

    // this tile covers the entire plane
    static const float VERTICES[NUM_VERTICES * 5] = {
        // x     y      z       texture coords
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  // front left
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,  // back left
         0.5f, -0.5f, -0.5f,    1.0f, 1.0f,  // back right
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f   // front right
    };

    static const GLuint NUM_INDEXES = 6;
    static const GLuint VERTICES_INDEXES[NUM_INDEXES] = {
        0, 1, 2,
        2, 3, 0,
    };
}

class Tile;
class Tiles {
public:
    Tiles();
    Tiles(const glm::mat4 & world_trans,
          unsigned int num_x,
          unsigned int num_z,
          const std::shared_ptr<ShaderHandler> & shader_handler,
          const std::shared_ptr<Texture> & texture);

    void draw() const;

private:
    glm::mat4 m_trans;
    std::vector<std::unique_ptr<Tile>> m_tiles;
};

class Tile {
public:
    friend class Tiles;

    Tile(const std::shared_ptr<ShaderHandler> & shader_handler,
         const glm::mat4 & trans,
         const std::shared_ptr<Texture> & texture);

    void draw(const glm::mat4 & world_trans = glm::mat4(1.0f)) const;

private:
    void init();

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

    glm::mat4 m_trans;

    std::shared_ptr<ShaderHandler> m_shader_handler;
    std::shared_ptr<Texture> m_texture;
};

