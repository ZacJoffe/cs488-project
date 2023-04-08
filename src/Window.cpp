#include "Window.h"

#include "GameState.h"
#include "MenuState.h"
#include "State.h"

#include <iostream>
#include <memory>

Window::Window() :
    m_delta_time(0.0f),
    m_last_frame_time(0.0f),
    m_curr_state_value(StateValue::Menu) {}

Window::~Window() {}

void Window::init() {
    ImGuiIO & io = ImGui::GetIO();
    m_font_title = io.Fonts->AddFontFromFileTTF("./assets/fonts/roboto/Roboto-Regular.ttf", 48);
    m_font_normal = io.Fonts->AddFontFromFileTTF("./assets/fonts/roboto/Roboto-Regular.ttf", 16);

    // always start in menu state
    m_curr_state = std::make_unique<MenuState>(m_framebufferWidth, m_framebufferHeight, m_font_title, m_font_normal);
    m_game_context = std::make_unique<GameContext>();
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::appLogic() {
    calculateDeltaTime();
    // std::cout << m_delta_time << std::endl;

    m_curr_state->appLogic(m_delta_time);
}

void Window::guiLogic() {
    m_curr_state->guiLogic(m_game_context);
    if (m_curr_state->switchStates()) {
        toggleState();
    }
}

void Window::draw() {
    m_curr_state->draw();
}

void Window::cleanup() {}


// EVENT HANDLERS
bool Window::cursorEnterWindowEvent(int entered) {
    return false;
}

bool Window::mouseMoveEvent(double xPos, double yPos) {
    m_curr_state->handleMouseMove(xPos, yPos);

    // this value is not used by the caller in the cs488 framework
    return false;
}

bool Window::mouseButtonInputEvent(int button, int actions, int mods) {
    m_curr_state->handleMouseButtonInput(button, actions, mods);

    return false;
}

bool Window::mouseScrollEvent(double xOffSet, double yOffSet) {
    return false;
}

bool Window::windowResizeEvent(int width, int height) {
    return false;
}

bool Window::keyInputEvent(int key, int action, int mods) {
    if (m_curr_state->handleKeyInput(key, action, mods)) {
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    }

    return true;
}

void Window::toggleState() {
    switch (m_curr_state_value) {
        case StateValue::Menu: {
            std::cout << "switching to game state" << std::endl;

            m_curr_state_value = StateValue::Game;
            m_curr_state = std::make_unique<GameState>(*m_game_context, m_framebufferWidth, m_framebufferHeight);
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        }
        case StateValue::Game: {
            std::cout << "switching to game state" << std::endl;

            m_curr_state_value = StateValue::Menu;
            m_curr_state = std::make_unique<MenuState>(m_framebufferWidth, m_framebufferHeight, m_font_title, m_font_normal);
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        }
    }
}

void Window::calculateDeltaTime() {
    const float current_frame_time = glfwGetTime();
    m_delta_time = current_frame_time - m_last_frame_time;
    m_last_frame_time = current_frame_time;
}

