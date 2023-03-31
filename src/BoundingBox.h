#pragma once

#include <glm/glm.hpp>
#include <string>

struct BoundingBox {
    glm::vec2 min;
    glm::vec2 max;
    BoundingBox(glm::vec2 min, glm::vec2 max);

    bool colliding(const BoundingBox & other) const;
    std::string toString() const;
};
