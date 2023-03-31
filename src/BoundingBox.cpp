#include "BoundingBox.h"

#include <glm/gtx/string_cast.hpp>

BoundingBox::BoundingBox(glm::vec2 min, glm::vec2 max) : min(min), max(max) {}

bool BoundingBox::collisionTest(const BoundingBox & other) const {
    return max.x >= other.min.x && other.max.x >= min.x
        && max.y >= other.min.y && other.max.y >= min.y;
}

std::string BoundingBox::toString() const {
    return "(" + glm::to_string(min) + ", " + glm::to_string(max) + ")";
}
