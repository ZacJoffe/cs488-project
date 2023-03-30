#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace camera_constants;

Camera::Camera() :
    m_yaw(DEFAULT_YAW),
    m_pitch(DEFAULT_PITCH) {}

Camera::Camera(const glm::vec3 & pos, const glm::vec3 & front, const glm::vec3 & up) :
    m_pos(pos),
    m_front(front),
    m_up(up),
    m_yaw(DEFAULT_YAW),
    m_pitch(DEFAULT_PITCH),
    m_prev_direction(MovementDirection::forward),
    m_speed(0.0f) {}

Camera::~Camera() {}

glm::mat4 Camera::getView() const {
    return glm::lookAt(
        m_pos,
        m_pos + m_front,
        m_up
    );
}

void Camera::updateDirection(float dx, float dy) {
    m_yaw += dx;
    m_pitch += dy;

    // TODO uncomment
    // glm::clamp(m_pitch, MIN_PITCH, MAX_PITCH);

    m_front = glm::normalize(
        glm::vec3(
            glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch)),
            glm::sin(glm::radians(m_pitch)),
            glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch))
        ));
}

void Camera::move(std::optional<MovementDirection> direction, float delta_time) {
    const float speed = m_speed * delta_time;
    const glm::vec3 right_axis = glm::normalize(glm::cross(m_front, m_up));
    const glm::vec3 forward_axis = glm::normalize(glm::cross(m_up, right_axis));
    const glm::vec3 forward_right_axis = glm::normalize(forward_axis + right_axis);
    const glm::vec3 forward_left_axis = glm::normalize(forward_axis - right_axis);

    if (direction) {
        glm::vec3 velocity;

        switch (*direction) {
            case MovementDirection::forward: {
                velocity = speed * forward_axis;
                break;
            }
            case MovementDirection::forward_right: {
                velocity = speed * forward_right_axis;
                break;
            }
            case MovementDirection::right: {
                velocity = speed * right_axis;
                break;
            }
            case MovementDirection::back_right: {
                // TODO make -1 some negative constant that limits backward movement speed
                velocity = -1 * speed * forward_left_axis;
                break;
            }
            case MovementDirection::back: {
                velocity = -1 * speed * forward_axis;
                break;
            }
            case MovementDirection::back_left: {
                velocity = -1 * speed * forward_right_axis;
                break;
            }
            case MovementDirection::left: {
                velocity = -1 * speed * right_axis;
                break;
            }
            case MovementDirection::forward_left: {
                velocity = speed * forward_left_axis;
                break;
            }
        }

        m_pos += velocity;

        if (m_speed < MAX_SPEED) {
            m_speed += ACCELERATION * delta_time;
        }

        m_prev_direction = *direction;
    } else {
        // no keys are being pressed, slow player down to stop if they are moving
    }
}
