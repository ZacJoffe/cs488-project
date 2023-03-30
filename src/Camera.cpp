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

    if (direction) {
        switch (*direction) {
            case MovementDirection::forward: {
                m_pos += speed * forward_axis;
                break;
            }
            case MovementDirection::forward_right: {
                m_pos += speed * forward_axis;
                m_pos += speed * right_axis;
                break;
            }
            case MovementDirection::right: {
                m_pos += speed * right_axis;
                break;
            }
            case MovementDirection::back_right: {
                m_pos -= speed * forward_axis;
                m_pos += speed * right_axis;
                break;
            }
            case MovementDirection::back: {
                m_pos -= speed * forward_axis;
                break;
            }
            case MovementDirection::back_left: {
                m_pos -= speed * forward_axis;
                m_pos -= speed * right_axis;
                break;
            }
            case MovementDirection::left: {
                m_pos -= speed * right_axis;
                break;
            }
            case MovementDirection::forward_left: {
                m_pos += speed * forward_axis;
                m_pos -= speed * right_axis;
                break;
            }
        }

        if (m_speed < MAX_SPEED) {
            m_speed += ACCELERATION * delta_time;
        }

        m_prev_direction = *direction;
    } else {
        // no keys are being pressed, slow player down to stop if they are moving
    }
}
