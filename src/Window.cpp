#include "Window.h"

#include "GameState.h"
#include "MenuState.h"
#include "State.h"

#include <iostream>
#include <memory>

Window::Window() :
    m_delta_time(0.0f),
    m_last_frame_time(0.0f),
    m_state_value(StateValue::Menu) {}

Window::~Window() {}

void Window::init() {
    // always start in menu state
    m_state = std::make_unique<MenuState>(m_framebufferWidth, m_framebufferHeight);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::appLogic() {
    calculateDeltaTime();
    // std::cout << m_delta_time << std::endl;

    m_state->appLogic(m_delta_time);
}

void Window::guiLogic() {
    m_state->guiLogic();
    if (m_state->switchStates()) {
        switchToGameState();
    }
}

void Window::draw() {
    m_state->draw();
}

void Window::cleanup() {}


// EVENT HANDLERS
bool Window::cursorEnterWindowEvent(int entered) {
    return false;
}

bool Window::mouseMoveEvent(double xPos, double yPos) {
    m_state->handleMouseMove(xPos, yPos);

    // this value is not used by the caller in the cs488 framework
    return false;
}

bool Window::mouseButtonInputEvent(int button, int actions, int mods) {
    m_state->handleMouseButtonInput(button, actions, mods);

    return false;
}

bool Window::mouseScrollEvent(double xOffSet, double yOffSet) {
    return false;
}

bool Window::windowResizeEvent(int width, int height) {
    return false;
}

bool Window::keyInputEvent(int key, int action, int mods) {
    if (m_state->handleKeyInput(key, action, mods)) {
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    }

    return true;
}

void Window::switchToGameState() {
    std::cout << "switching to game state" << std::endl;

    m_state_value = StateValue::Game;
    // TODO make game context be returned from menu state
    m_state = std::make_unique<GameState>(GameContext(), m_framebufferWidth, m_framebufferHeight);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::calculateDeltaTime() {
    const float current_frame_time = glfwGetTime();
    m_delta_time = current_frame_time - m_last_frame_time;
    m_last_frame_time = current_frame_time;
}

