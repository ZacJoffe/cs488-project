#include "KeyInputHandler.hpp"

#include <iostream>

KeyInputHandler::KeyInputHandler() {}

void KeyInputHandler::pressKey(int key) {
    setKeyHelper(key, true);
}

void KeyInputHandler::releaseKey(int key) {
    setKeyHelper(key, false);
}

void KeyInputHandler::performAction(Camera & camera) {
    // NOTE this works since a kvp that doesn't exist will be inserted with a
    // default value of false when using operator[]
    if (m_key_states[Key::W]) {
        camera.move(MovementDirection::forward);
    }
    if (m_key_states[Key::S]) {
        camera.move(MovementDirection::backward);
    }
    if (m_key_states[Key::A]) {
        camera.move(MovementDirection::left);
    }
    if (m_key_states[Key::D]) {
        camera.move(MovementDirection::right);
    }
}


void KeyInputHandler::setKeyHelper(int key, bool action) {
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
