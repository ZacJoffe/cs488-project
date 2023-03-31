#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace camera_constants;
using namespace physics_constants;

Camera::Camera(const glm::vec3 & pos, const glm::vec3 & front, const glm::vec3 & up) :
    m_pos(pos),
    m_front(front),
    m_up(up),
    m_initial_y(pos.y),
    m_yaw(DEFAULT_YAW),
    m_pitch(DEFAULT_PITCH),
    m_prev_direction(MovementDirection::forward),
    m_speed_xz(0.0f),
    m_velocity_y(0.0f),
    m_jumping(false),
    m_sprinting(false)
{
    m_bounding_box_xy = std::make_unique<BoundingBox>(glm::vec2(), glm::vec2());
}

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

    // std::cout << m_pitch << std::endl;
    m_pitch = glm::clamp(m_pitch, MIN_PITCH, MAX_PITCH);

    m_front = glm::normalize(
        glm::vec3(
            glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch)),
            glm::sin(glm::radians(m_pitch)),
            glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch))
        ));
}

void Camera::move(std::optional<MovementDirection> direction, float delta_time) {
    updateBoundingBoxXZ();

    const glm::vec3 right_axis = glm::normalize(glm::cross(m_front, m_up));
    const glm::vec3 forward_axis = glm::normalize(glm::cross(m_up, right_axis));
    const glm::vec3 forward_right_axis = glm::normalize(forward_axis + right_axis);
    const glm::vec3 forward_left_axis = glm::normalize(forward_axis - right_axis);

    auto calculateVelocityXZ = [delta_time, &right_axis, &forward_axis, &forward_right_axis, &forward_left_axis, this](MovementDirection direction) {
        const float speed = m_speed_xz * delta_time;
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
                // TODO replace -1 with some negative constant that limits backward movement speed
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
        throw std::domain_error("Should never reach outside of exhaustive switch");
    };

    // approximate integral in movement equations in the rest of this method with semi-implicit euler integrator
    // https://gafferongames.com/post/integration_basics/
    if (direction) {
        if (m_sprinting) {
            if (m_speed_xz < MAX_SPRINT_SPEED) {
                m_speed_xz += ACCELERATION * delta_time;
            }

            const glm::vec3 velocity = calculateVelocityXZ(*direction);
            m_pos += velocity;

            // clamp speed
            if (m_speed_xz > MAX_SPRINT_SPEED) {
                m_speed_xz = MAX_SPRINT_SPEED;
            }
        } else if (m_speed_xz > MAX_WALK_SPEED && m_speed_xz <= MAX_SPRINT_SPEED) {
            // slow player down from sprint to normal walking speed
            m_speed_xz += -1 * ACCELERATION * delta_time;
            const glm::vec3 velocity = calculateVelocityXZ(m_prev_direction);
            m_pos += velocity;
        } else {
            if (m_speed_xz < MAX_WALK_SPEED) {
                m_speed_xz += ACCELERATION * delta_time;
            }

            const glm::vec3 velocity = calculateVelocityXZ(*direction);
            m_pos += velocity;

            if (m_speed_xz > MAX_WALK_SPEED) {
                m_speed_xz = MAX_WALK_SPEED;
            }
        }

        m_prev_direction = *direction;
    } else if (m_speed_xz > MIN_SPEED) {
        // no keys are being pressed and player is moving, slow player down to stop
        m_speed_xz += -1 * ACCELERATION * delta_time;
        const glm::vec3 velocity = calculateVelocityXZ(m_prev_direction);
        m_pos += velocity;

        // explicitly clamp speed to 0 to avoid numerical headaches
        if (m_speed_xz < MIN_SPEED) {
            m_speed_xz = 0.0f;
        }
    }

    if (m_jumping) {
        m_velocity_y += GRAVITY * delta_time;
        m_pos.y += m_velocity_y * delta_time;

        if (m_pos.y <= m_initial_y) {
            m_pos.y = m_initial_y;
            m_jumping = false;
        }
    }

    debugCameraPrint();
}

void Camera::initiateJump() {
    if (!m_jumping) {
        m_jumping = true;
        m_velocity_y = INITIAL_JUMP_VELOCITY;
    }
}

void Camera::startSprint() {
    m_sprinting = true;
}

void Camera::stopSprint() {
    m_sprinting = false;
}

void Camera::debugCameraPrint() const {
    std::cout << "Position: " << glm::to_string(m_pos)
              // << ", Front: " << glm::to_string(m_front)
              // << ", Speed " << m_speed_xz
              << ", Bounding Box: (" << glm::to_string(m_bounding_box_xy->min) << ", " << glm::to_string(m_bounding_box_xy->max) << ")"
              << std::endl;
}

void Camera::updateBoundingBoxXZ() {
    m_bounding_box_xy->min = glm::vec2(m_pos.x - BOUNDING_BOX_OFFSET, m_pos.z - BOUNDING_BOX_OFFSET);
    m_bounding_box_xy->max = glm::vec2(m_pos.x + BOUNDING_BOX_OFFSET, m_pos.z + BOUNDING_BOX_OFFSET);
}
