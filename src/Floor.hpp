#pragma once

#include "Geometry.hpp"

namespace floor_constants {
    const size_t NUM_VERTICES = 4;

    // this floor covers the entire plane
    const float VERTICES[NUM_VERTICES * 3] = {
        // x, y, z, right hand coordinate system
        -1.0f, 0.0f, 1.0f,   // front left
        -1.0f, 0.0f, -1.0f,  // back left
        1.0f, 0.0f, -1.0f,   // back right
        1.0f, 0.0f, 1.0f,    // front right
    };
}

class Floor : public Geometry {
public:
    Floor();
    ~Floor() override;

    void draw(GLint color_uni) override();

private:
    void init() override;
}
