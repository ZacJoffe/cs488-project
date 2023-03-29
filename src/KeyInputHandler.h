#pragma once

#include "GLFW/glfw3.h"
#include "Camera.h"

#include <memory>
#include <unordered_map>

class KeyInputHandler {
public:
    KeyInputHandler();

    void pressKey(int key);
    void releaseKey(int key);

    void performAction(Camera & camera);

private:
    enum class Key {
        W = GLFW_KEY_W,
        S = GLFW_KEY_S,
        A = GLFW_KEY_A,
        D = GLFW_KEY_D,
    };

    void setKeyHelper(int key, bool action);

    std::unordered_map<Key, bool> m_key_states;
};
