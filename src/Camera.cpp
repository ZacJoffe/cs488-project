#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

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
    const glm::vec3 right_axis = glm::normalize(glm::cross(m_front, m_up));
    const glm::vec3 forward_axis = glm::normalize(glm::cross(m_up, right_axis));
    const glm::vec3 forward_right_axis = glm::normalize(forward_axis + right_axis);
    const glm::vec3 forward_left_axis = glm::normalize(forward_axis - right_axis);

    auto calculateVelocity = [delta_time, &right_axis, &forward_axis, &forward_right_axis, &forward_left_axis, this](MovementDirection direction) {
        const float speed = m_speed * delta_time;
        switch (direction) {
            case MovementDirection::forward: {
                return speed * forward_axis;
            }
            case MovementDirection::forward_right: {
                return speed * forward_right_axis;
            }
            case MovementDirection::right: {
                return speed * right_axis;
            }
            case MovementDirection::back_right: {
                // TODO make -1 some negative constant that limits backward movement speed
                return -1 * speed * forward_left_axis;
            }
            case MovementDirection::back: {
                return -1 * speed * forward_axis;
            }
            case MovementDirection::back_left: {
                return -1 * speed * forward_right_axis;
            }
            case MovementDirection::left: {
                return -1 * speed * right_axis;
            }
            case MovementDirection::forward_left: {
                return speed * forward_left_axis;
            }
        }

        // this should never be reached but the compiler isn't smart enough to
        // deduce this face inside the lambda and produces a warning
        throw std::domain_error("Should never outside of exhaustive switch");
    };

    if (direction) {
        const glm::vec3 velocity = calculateVelocity(*direction);
        m_pos += velocity;

        if (m_speed < MAX_SPEED) {
            m_speed += ACCELERATION * delta_time;
        }

        m_prev_direction = *direction;
    } else if (m_speed > MIN_SPEED) {
        // no keys are being pressed and player is moving, slow player down to stop
        const glm::vec3 velocity = calculateVelocity(m_prev_direction);
        m_pos += velocity;
        m_speed += -1 * ACCELERATION * delta_time;

        // explicitly clamp speed to 0 to avoid numerical headaches
        if (m_speed < MIN_SPEED) {
            m_speed = 0.0f;
        }
    }
}
