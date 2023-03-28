#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {}

Camera::Camera(const glm::vec3 & pos, const glm::vec3 & front, const glm::vec3 & up) :
    m_pos(pos), m_front(front), m_up(up) {}

Camera::~Camera() {}

glm::mat4 Camera::getView() const {
    return glm::lookAt(
        m_pos,
        m_pos + m_front,
        m_up
    );
}

void Camera::move(MovementDirection direction) {
    const float speed = 0.5f;
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
