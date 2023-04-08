#include "BoundingBox.h"

#include <glm/gtx/string_cast.hpp>

BoundingBox::BoundingBox() {}

BoundingBox::BoundingBox(glm::vec2 min, glm::vec2 max) : min(min), max(max) {}

bool BoundingBox::collisionTest(const BoundingBox & other) const {
    return max.x >= other.min.x && other.max.x >= min.x
        && max.y >= other.min.y && other.max.y >= min.y;
}

std::string BoundingBox::toString() const {
    return "(" + glm::to_string(min) + ", " + glm::to_string(max) + ")";
}

std::list<LineSegment> BoundingBox::getLineSegments() const {
    /*
    2D (x-z plane) diagram of scene
               top
    ^       +--------+ max
    |       +        +
    |       +        +
    |       +        +
    |  left +        + right
    |       +        +
    |       +        +
    |       +        +
    |       +        +
    |   min +--------+
    |         bottom
    x
     z-------------------->
    */

    return {
        { min, glm::vec2(max.x, min.y) }, // left
        { glm::vec2(max.x, min.y), max }, // top
        { glm::vec2(min.x, max.y), max }, // right
        { min, glm::vec2(min.x, max.y) }, // bottom
    };
}

