#include "InputHandler.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <optional>
#include <utility>

InputHandler::InputHandler() :
    m_prev_cursor_pos(0.0f, 0.0f),
    m_cursor_pos_deltas(0.0f, 0.0f) {}

void InputHandler::pressKey(int key) {
    setKeyHelper(key, true);
}

void InputHandler::releaseKey(int key) {
    setKeyHelper(key, false);
}

void InputHandler::updateCursorPos(const std::pair<float, float> & cursor_pos) {
    m_cursor_pos_deltas.first = (cursor_pos.first - m_prev_cursor_pos.first);
    m_cursor_pos_deltas.second = (m_prev_cursor_pos.second - cursor_pos.second);
    m_prev_cursor_pos = cursor_pos;
}

std::pair<float, float> InputHandler::getCursorDeltas() const {
    return m_cursor_pos_deltas;
}

Actions InputHandler::getActions() {
    bool initiateJump = false, sprint = false;

    if (m_key_states[Key::Space]) {
        initiateJump = true;
    }

    if (m_key_states[Key::Shift]) {
        sprint = true;
    }

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

    return Actions(direction, initiateJump, sprint);
}

void InputHandler::setKeyHelper(int key, bool is_pressed) {
    switch (key) {
        case GLFW_KEY_W: {
            if (is_pressed) {
                std::cout << "w key pressed" << std::endl;
            } else {
                std::cout << "w key released" << std::endl;
            }
            m_key_states[Key::W] = is_pressed;
            return;
        }
        case GLFW_KEY_S: {
            if (is_pressed) {
                std::cout << "s key pressed" << std::endl;
            } else {
                std::cout << "s key released" << std::endl;
            }
            m_key_states[Key::S] = is_pressed;
            return;
        }
        case GLFW_KEY_A: {
            if (is_pressed) {
                std::cout << "a key pressed" << std::endl;
            } else {
                std::cout << "a key released" << std::endl;
            }
            m_key_states[Key::A] = is_pressed;
            return;
        }
        case GLFW_KEY_D: {
            if (is_pressed) {
                std::cout << "d key pressed" << std::endl;
            } else {
                std::cout << "d key released" << std::endl;
            }
            m_key_states[Key::D] = is_pressed;
            return;
        }
        case GLFW_KEY_SPACE: {
            if (is_pressed) {
                std::cout << "space key pressed" << std::endl;
            } else {
                std::cout << "space key released" << std::endl;
            }
            m_key_states[Key::Space] = is_pressed;
            return;
        }
        case GLFW_KEY_LEFT_SHIFT: {
            if (is_pressed) {
                std::cout << "shift key pressed" << std::endl;
            } else {
                std::cout << "shift key released" << std::endl;
            }
            m_key_states[Key::Shift] = is_pressed;
            return;
        }
    }
}

