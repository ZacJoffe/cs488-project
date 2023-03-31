#pragma once

#include "ShaderHandler.h"
#include "Texture.h"
#include "Tile.h"

#include <array>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class Scene {
public:
    Scene();

    void draw(const glm::mat4 & projection, const glm::mat4 & view, const glm::mat4 & model);

private:
    std::shared_ptr<ShaderHandler> m_shader_handler;

    std::shared_ptr<Texture> m_floor_texture;
    Tiles m_floor;

    std::shared_ptr<Texture> m_wall_texture;
    std::array<Tiles, 4> m_walls;
};
