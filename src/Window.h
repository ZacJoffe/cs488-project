#pragma once

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "GameContext.h"
#include "GameState.h"
#include "MenuState.h"
#include "State.h"
#include <imgui.h>

#include <memory>
#include <string>

class Window {
public:
    static Window & getInstance();
    Window(Window const &) = delete;
    void operator=(Window const &) = delete;

    void launch(int width, int height, const std::string & title, float fps = 60.0f);

private:
    Window();

    void run(int width, int height, const std::string & window_title, float target_fps);
    void register_glfw_callbacks();

    void init();
    void appLogic();
    void guiLogic();
    void draw();

    // void cursorEnterWindowEvent(int entered);
    void cursorPositionEvent(double xpos, double ypos);
    void mouseButtonInputEvent(int button, int action, int mods);
    // void mouseScrollEvent(double xoffset, double yoffset);
    void windowResizeEvent(int width, int height);
    void keyInputEvent(int key, int action, int mods);

    void toggleState();
    void calculateDeltaTime();

    // GLFWmonitor * m_monitor;
    GLFWwindow * m_window;
    std::string m_window_title;
    int m_window_width;
    int m_window_height;
    int m_framebuffer_width;
    int m_framebuffer_height;

    StateValue m_curr_state_value;
    std::unique_ptr<State> m_curr_state;
    // std::shared_ptr<MenuState> m_menu_state;
    // std::shared_ptr<GameState> m_game_state;
    std::unique_ptr<GameContext> m_game_context;

    ImFont * m_font_title;
    ImFont * m_font_normal;

    float m_delta_time;
    float m_last_frame_time;
};

