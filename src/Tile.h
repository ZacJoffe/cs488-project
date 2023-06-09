#pragma once

#include "BoundingBox.h"
#include "ShaderHandler.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace tile_constants {
    static const GLuint NUM_VERTICES = 4;

    // this tile covers the entire plane
    static const float VERTICES[NUM_VERTICES * 3] = {
        // x    y    z
        0.0f, 0.0f, 1.0f,  // front left
        0.0f, 0.0f, 0.0f,  // back left
        1.0f, 0.0f, 0.0f,  // back right
        1.0f, 0.0f, 1.0f   // front right
    };

    static const float NORMALS[NUM_VERTICES * 3] = {
        // x    y    z
        0.0f, 1.0f, 0.0f,  // front left
        0.0f, 1.0f, 0.0f,  // back left
        0.0f, 1.0f, 0.0f,  // back right
        0.0f, 1.0f, 0.0f   // front right
    };

    static const float UV_COORDS[NUM_VERTICES * 2] = {
        0.0f, 0.0f,  // front left
        0.0f, 1.0f,  // back left
        1.0f, 1.0f,  // back right
        1.0f, 0.0f   // front right
    };


    static const GLuint NUM_INDEXES = 6;
    static const GLuint VERTICES_INDEXES[NUM_INDEXES] = {
        0, 1, 2,
        2, 3, 0,
    };
}

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
    GLuint m_vbo_vertices;
    GLuint m_vbo_normals;
    GLuint m_vbo_uvs;
    GLuint m_ebo;

    glm::mat4 m_trans;

    std::shared_ptr<ShaderHandler> m_shader_handler;
    std::shared_ptr<Texture> m_texture;
};

class Tiles {
public:
    Tiles();
    Tiles(const glm::mat4 & world_trans,
          unsigned int num_x,
          unsigned int num_z,
          const std::shared_ptr<ShaderHandler> & shader_handler,
          const std::shared_ptr<Texture> & texture,
          std::shared_ptr<BoundingBox> bounding_box_xy);

    void draw() const;
    std::shared_ptr<BoundingBox> getBoundingBox() const;

private:
    glm::mat4 m_trans;
    std::vector<std::unique_ptr<Tile>> m_tiles;
    // if the bounding box is nullptr, then the object represented by the tiles is uncollidable
    std::shared_ptr<BoundingBox> m_bounding_box_xy; // min, max
};

