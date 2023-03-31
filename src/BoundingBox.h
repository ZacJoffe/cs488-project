#pragma once

#include <glm/glm.hpp>

struct BoundingBox {
    glm::vec2 min;
    glm::vec2 max;
    BoundingBox(glm::vec2 min, glm::vec2 max) : min(min), max(max) {}
};
