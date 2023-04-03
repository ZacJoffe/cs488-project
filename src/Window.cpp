#include "Window.h"

#include "GameState.h"
#include "MenuState.h"
#include "imgui.h"

#include <iostream>
#include <memory>

Window::Window() :
    m_delta_time(0.0f),
    m_last_frame_time(0.0f) {}

Window::~Window() {}

void Window::init() {
    // m_state = std::make_unique<GameState>(m_framebufferWidth, m_framebufferHeight);
    // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_state = std::make_unique<MenuState>();
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // DELETEME after doing the ui objective
    // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // std::cout << glfwGetInputMode(m_window, GLFW_CURSOR) << std::endl;
}

void Window::appLogic() {
    calculateDeltaTime();
    // std::cout << m_delta_time << std::endl;

    m_state->appLogic(m_delta_time);
}

void Window::guiLogic() {
    // DELETEME after doing the ui objective
    // std::cout << glfwGetInputMode(m_window, GLFW_CURSOR) << std::endl;

    ImGuiIO& io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
    m_state->guiLogic();
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

void Window::calculateDeltaTime() {
    const float current_frame_time = glfwGetTime();
    m_delta_time = current_frame_time - m_last_frame_time;
    m_last_frame_time = current_frame_time;
}

