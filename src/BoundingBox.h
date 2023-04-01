#pragma once

#include <glm/glm.hpp>
#include <list>
#include <string>
#include <utility>

using LineSegment = std::pair<glm::vec2, glm::vec2>;

struct BoundingBox {
    glm::vec2 min;
    glm::vec2 max;
    BoundingBox();
    BoundingBox(glm::vec2 min, glm::vec2 max);

    bool collisionTest(const BoundingBox & other) const;
    std::string toString() const;

    std::list<LineSegment> getLineSegments() const;
};
