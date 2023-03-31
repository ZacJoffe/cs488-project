#pragma once

#include "GLFW/glfw3.h"
#include "Actions.h"
#include "Camera.h"

#include <memory>
#include <unordered_map>
#include <utility>

class InputHandler {
public:
    InputHandler(float window_width, float window_height);

    void pressKey(int key);
    void releaseKey(int key);
    void updateCursorPos(const std::pair<float, float> & cursor_pos);

    std::pair<float, float> getCursorDeltas() const;
    // cannot be const since this technically modifies m_key_states
    Actions getActions();

private:
    enum class Key {
        W = GLFW_KEY_W,
        S = GLFW_KEY_S,
        A = GLFW_KEY_A,
        D = GLFW_KEY_D,
        Space = GLFW_KEY_SPACE,
        Shift = GLFW_KEY_LEFT_SHIFT,
    };

    void setKeyHelper(int key, bool is_pressed);

    std::unordered_map<Key, bool> m_key_states;
    std::pair<float, float> m_prev_cursor_pos;
    std::pair<float, float> m_cursor_pos_deltas;
};
