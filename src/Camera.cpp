#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace camera_constants;

Camera::Camera() :
    m_yaw(DEFAULT_YAW),
    m_pitch(DEFAULT_PITCH) {}

Camera::Camera(const glm::vec3 & pos, const glm::vec3 & front, const glm::vec3 & up) :
    m_pos(pos), m_front(front), m_up(up), m_yaw(DEFAULT_YAW), m_pitch(DEFAULT_PITCH) {}

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

void Camera::move(MovementDirection direction) {
    const float speed = 0.05f;
    switch (direction) {
        case MovementDirection::forward: {
            m_pos += speed * m_front;
            break;
        }
        case MovementDirection::backward: {
            m_pos -= speed * m_front;
            break;
        }
        case MovementDirection::left: {
            glm::vec3 right_axis = glm::normalize(glm::cross(m_front, m_up));
            m_pos -= speed * right_axis;
            break;
        }
        case MovementDirection::right: {
            glm::vec3 right_axis = glm::normalize(glm::cross(m_front, m_up));
            m_pos += speed * right_axis;
            break;
        }
    }
}
