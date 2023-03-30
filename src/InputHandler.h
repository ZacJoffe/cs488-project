#pragma once

#include "GLFW/glfw3.h"
#include "Camera.h"

#include <memory>
#include <unordered_map>
#include <utility>

class InputHandler {
public:
    InputHandler(float window_width, float window_height);

    void setCamera(const std::shared_ptr<Camera> & camera);

    void pressKey(int key);
    void releaseKey(int key);

    void performActions(float delta_time);

    void updateCursorPos(const std::pair<float, float> & cursor_pos);

private:
    enum class Key {
        W = GLFW_KEY_W,
        S = GLFW_KEY_S,
        A = GLFW_KEY_A,
        D = GLFW_KEY_D,
    };

    void setKeyHelper(int key, bool action);

    std::shared_ptr<Camera> m_camera;
    std::unordered_map<Key, bool> m_key_states;
    std::pair<float, float> m_prev_cursor_pos;
};
