#include "Ray.h"

#include <cmath>

using namespace ray_constants;

Ray::Ray(glm::vec3 e, glm::vec3 d) : e(e), d(d) {}

glm::vec3 Ray::operator()(float t) const {
    return e + t * d;
};

bool Ray::collisionTestXZ(const std::list<LineSegment> & line_segments) const {
    for (const auto & line_segment : line_segments) {
        if (collisionTestHelper(line_segment)) {
            return true;
        }
    }

    return false;
}

bool Ray::collisionTestHelper(const LineSegment & line_segment) const {
    const float e_x = e.x;
    const float e_z = e.z;
    const float d_x = d.x;
    const float d_z = d.z;

    const glm::vec2 P_0 = line_segment.first;
    const float x_0 = P_0.x;
    const float z_0 = P_0.y;

    const glm::vec2 P_1 = line_segment.second;
    const float x_1 = P_1.x;
    const float z_1 = P_1.y;

    const float den = (d_z * (x_1 - x_0) - d_x * (z_1 - z_0));
    if (std::fabs(den) < EPSILON) {
        return false;
    }

    const float s = (d_x * (z_0 - e_z) + d_z * (e_x - x_0)) / den;
    return s >= 0 && s <= 1;
}
