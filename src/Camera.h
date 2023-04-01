#pragma once

#include "BoundingBox.h"

#include "Actions.h"
#include "InputHandler.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include <list>
#include <memory>
#include <optional>
#include <utility>

namespace camera_constants {
    static const float DEFAULT_YAW = -45.0f;
    static const float DEFAULT_PITCH = 45.0f;
    static const float SENSITIVITY = 0.1f;

    static const float MIN_PITCH = -80.0f;
    static const float MAX_PITCH = 80.0f;
    static const float BOUNDING_BOX_OFFSET = 0.2f;
}

namespace physics_constants {
    // TODO change this for the demo?
    static const float ACCELERATION = 50.0f;
    static const float MAX_WALK_SPEED = 5.0f;
    static const float MAX_SPRINT_SPEED = 15.0f;
    static const float MIN_SPEED = 0.0f;

    static const float INITIAL_JUMP_VELOCITY = 5.0f;
    static const float GRAVITY = -10.0f;
}

class InputHandler;

class Camera {
public:
    Camera(const glm::vec3 & pos, const glm::vec3 & front, const glm::vec3 & up);
    ~Camera();

    glm::mat4 getView() const;

    // TODO move around, look around
    // also update the view uniform in this class for now I'll do it in window?
    void move(InputHandler & input_handler, const Scene & scene, float delta_time);
    // void updateDirection(float dx, float dy);
    void updateDirection(const InputHandler & input_handler);

    void debugCameraPrint() const;

private:
    BoundingBox updateBoundingBoxHelper(const glm::vec3 & pos) const;
    void updateBoundingBoxXZ();
    void initiateJump();
    void updatePosition(const glm::vec3 & velocity, std::list<BoundingBox> collidable_objects);

    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_up;

    float m_initial_y;

    float m_yaw;
    float m_pitch;

    MovementDirection m_prev_direction;
    float m_speed_xz;

    // jumping physics is 1D, therefore we can represent vectors as floats where
    // the direction is represented with their signs
    float m_velocity_y;
    bool m_jumping;

    bool m_sprinting;

    BoundingBox m_bounding_box_xz; // min, max
};

