#pragma once

#include <optional>

// 8-directional movement
enum class MovementDirection {
    forward,
    forward_right,
    right,
    back_right,
    back,
    back_left,
    left,
    forward_left,
};

struct Actions {
    std::optional<MovementDirection> direction;
    bool initiate_jump;
    bool sprint;
    Actions(const std::optional<MovementDirection> & direction, bool initiate_jump, bool sprint) :
        direction(direction), initiate_jump(initiate_jump), sprint(sprint) {}
};
