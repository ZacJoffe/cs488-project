#pragma once

#include <glm/glm.hpp>
#include <optional>

namespace camera_constants {
    static const float DEFAULT_YAW = -90.0f;
    static const float DEFAULT_PITCH = 0.0f; // TODO figure out bug with starting camera position
    static const float SENSITIVITY = 0.1f;

    static const float MIN_PITCH = -89.0f;
    static const float MAX_PITCH = +89.0f;

    static const float ACCELERATION = 100.0f; // TODO tweak this value
    static const float MAX_SPEED = 5.0f;
}

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

class Camera {
public:
    Camera();
    Camera(const glm::vec3 & pos, const glm::vec3 & front, const glm::vec3 & up);
    ~Camera();

    glm::mat4 getView() const;
    void updateDirection(float dx, float dy);

    // TODO move around, look around
    // also update the view uniform in this class for now I'll do it in window?
    void move(std::optional<MovementDirection> direction, float delta_time);

private:
    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_up;

    float m_yaw;
    float m_pitch;

    MovementDirection m_prev_direction;
    float m_speed;
};
