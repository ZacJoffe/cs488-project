#pragma once

#include "ShaderHandler.h"
#include "Tile.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

class Scene {
public:
    Scene();

    void draw(const glm::mat4 & projection, const glm::mat4 & view, const glm::mat4 & model);

private:
    std::shared_ptr<ShaderHandler> m_shader_handler;

    Tiles m_floor;
};
