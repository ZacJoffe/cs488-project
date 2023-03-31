#include "BoundingBox.h"

#include <glm/gtx/string_cast.hpp>

BoundingBox::BoundingBox(glm::vec2 min, glm::vec2 max) : min(min), max(max) {}

bool BoundingBox::colliding(const BoundingBox & other) const {
    // TODO
    return false;
}

std::string BoundingBox::toString() const {
    return "(" + glm::to_string(min) + ", " + glm::to_string(max) + ")";
}
