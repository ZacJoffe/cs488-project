#include "InputHandler.h"
#include "Camera.h"

#include <iostream>
#include <optional>
#include <utility>

InputHandler::InputHandler(float window_width, float window_height) :
    m_prev_cursor_pos(window_width / 2.0f, window_height / 2.0f) {}

void InputHandler::setCamera(const std::shared_ptr<Camera> & camera) {
    m_camera = camera;
}

void InputHandler::pressKey(int key) {
    setKeyHelper(key, true);
}

void InputHandler::releaseKey(int key) {
    setKeyHelper(key, false);
}

void InputHandler::performActions(float delta_time) {
    std::optional<MovementDirection> direction = {};

    // NOTE this works since a kvp that doesn't exist will be inserted with a
    // default value of false when using operator[]
    if (m_key_states[Key::W]) {
        if (m_key_states[Key::A]) {
            direction = MovementDirection::forward_left;
        } else if (m_key_states[Key::D]) {
            direction = MovementDirection::forward_right;
        } else {
            direction = MovementDirection::forward;
        }
    } else if (m_key_states[Key::S]) {
        if (m_key_states[Key::A]) {
            direction = MovementDirection::back_left;
        } else if (m_key_states[Key::D]) {
            direction = MovementDirection::back_right;
        } else {
            direction = MovementDirection::back;
        }
    } else if (m_key_states[Key::A]) {
        direction = MovementDirection::left;
    } else if (m_key_states[Key::D]) {
        direction = MovementDirection::right;
    }

    m_camera->move(direction, delta_time);
}


void InputHandler::updateCursorPos(const std::pair<float, float> & cursor_pos) {
    const float dx = (cursor_pos.first - m_prev_cursor_pos.first) * camera_constants::SENSITIVITY;
    const float dy = (m_prev_cursor_pos.second - cursor_pos.second) * camera_constants::SENSITIVITY;
    m_prev_cursor_pos = cursor_pos;

    m_camera->updateDirection(dx, dy);
}

void InputHandler::setKeyHelper(int key, bool action) {
    switch (key) {
        case GLFW_KEY_W: {
            if (action) {
                std::cout << "w key pressed" << std::endl;
            } else {
                std::cout << "w key released" << std::endl;
            }
            m_key_states[Key::W] = action;
            return;
        }
        case GLFW_KEY_S: {
            if (action) {
                std::cout << "s key pressed" << std::endl;
            } else {
                std::cout << "s key released" << std::endl;
            }
            m_key_states[Key::S] = action;
            return;
        }
        case GLFW_KEY_A: {
            if (action) {
                std::cout << "a key pressed" << std::endl;
            } else {
                std::cout << "a key released" << std::endl;
            }
            m_key_states[Key::A] = action;
            return;
        }
        case GLFW_KEY_D: {
            if (action) {
                std::cout << "d key pressed" << std::endl;
            } else {
                std::cout << "d key released" << std::endl;
            }
            m_key_states[Key::D] = action;
            return;
        }
    }
}
