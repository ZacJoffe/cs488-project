#include "InputHandler.h"

#include <iostream>
#include <utility>

InputHandler::InputHandler() {}

void InputHandler::setCamera(const std::shared_ptr<Camera> & camera) {
    m_camera = camera;
}

void InputHandler::setInitialCursorPosition(const std::pair<float, float> & cursor_pos) {
    m_prev_cursor_pos = cursor_pos;
}

void InputHandler::pressKey(int key) {
    setKeyHelper(key, true);
}

void InputHandler::releaseKey(int key) {
    setKeyHelper(key, false);
}

void InputHandler::performActions() {
    // NOTE this works since a kvp that doesn't exist will be inserted with a
    // default value of false when using operator[]
    if (m_key_states[Key::W]) {
        m_camera->move(MovementDirection::forward);
    }
    if (m_key_states[Key::S]) {
        m_camera->move(MovementDirection::backward);
    }
    if (m_key_states[Key::A]) {
        m_camera->move(MovementDirection::left);
    }
    if (m_key_states[Key::D]) {
        m_camera->move(MovementDirection::right);
    }
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
