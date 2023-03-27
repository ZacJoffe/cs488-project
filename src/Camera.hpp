#pragma once

#include <glm/glm.hpp>

class Camera {
public:
    Camera(const glm::vec3 & pos, const glm::vec3 & front, const glm::vec3 & up);
    ~Camera();

    glm::mat4 getView() const;

    // TODO move around, look around
    // also update the view uniform in this class for now I'll do it in window?

private:
    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_up;
};
