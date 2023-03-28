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

