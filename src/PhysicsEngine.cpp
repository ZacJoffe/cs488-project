#include "PhysicsEngine.h"

using namespace physics_constants;

PhysicsEngine::PhysicsEngine() : m_speed_xz(0.0f), m_velocity_y(0.0f) {}

void PhysicsEngine::tick(const Actions & actions) {

}

void PhysicsEngine::initiateJump() {
    m_velocity_y = INITIAL_JUMP_VELOCITY;
}

