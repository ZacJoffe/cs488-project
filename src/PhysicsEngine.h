#pragma once

#include "Actions.h"

#include <optional>

namespace physics_constants {
    static const float ACCELERATION = 50.0f;
    static const float MAX_WALK_SPEED = 5.0f;
    static const float MAX_SPRINT_SPEED = 15.0f;
    static const float MIN_SPEED = 0.0f;

    static const float INITIAL_JUMP_VELOCITY = 5.0f;
    static const float GRAVITY = -10.0f;
}

class PhysicsEngine {
public:
    PhysicsEngine();
    // void tick(const std::optional<MovementDirection> & direction, bool jumping, bool sprinting);
    void tick(const Actions & actions);
    void initiateJump();

private:
    float m_speed_xz;

    // jumping physics is 1D, therefore we can represent vectors as floats where
    // the direction is represented with their signs
    float m_velocity_y;
};

