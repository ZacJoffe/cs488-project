#pragma once

#include <glm/glm.hpp>
#include <list>
#include <utility>

using LineSegment = std::pair<glm::vec2, glm::vec2>;

namespace ray_constants {
    // TODO adjust
    static const float EPSILON = 0.001f;
}

class Ray {
public:
    glm::vec3 e; // start position
    glm::vec3 d; // direction of ray

    Ray(glm::vec3 e, glm::vec3 d);
    glm::vec3 operator()(float t) const;
    bool collisionTestXZ(const std::list<LineSegment> & line_segments) const;

private:
    bool collisionTestHelper(const LineSegment & line_segment) const;
};

