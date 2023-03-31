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
    bool initiateJump;
    bool sprint;
    Actions(const std::optional<MovementDirection> & direction, bool initiateJump, bool sprint) : direction(direction), initiateJump(initiateJump), sprint(sprint) {}
};
