#pragma once

#include "ShaderHandler.h"
#include "Texture.h"
#include "Tile.h"

#include <array>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace scene_constants {
    // N x Y x N world
    static const float N = 50.0f;
    static const float Y = 5.0f;
    static const glm::vec3 WORLD_BOUNDARY_MIN = glm::vec3(0.0f, 2.0f, 0.0f);
    static const glm::vec3 WORLD_BOUNDARY_MAX = glm::vec3(N, Y, N);
}

class Scene {
public:
    Scene();

    void draw(const glm::mat4 & projection, const glm::mat4 & view, const glm::mat4 & model);

private:
    void initFloor();
    void initWalls();

    std::shared_ptr<ShaderHandler> m_shader_handler;

    std::shared_ptr<Texture> m_floor_texture;
    Tiles m_floor;

    std::shared_ptr<Texture> m_wall_texture;
    std::array<Tiles, 4> m_walls;
};
