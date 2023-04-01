#include "Window.h"

#include "cs488-framework/GlErrorCheck.hpp"
#include "imgui.h"
#include "Ray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <utility>

using namespace window_constants;

Window::Window() :
    m_input_handler(m_windowHeight, m_windowWidth),
    m_delta_time(0.0f),
    m_last_frame_time(0.0f),
    m_shooting(false) {}

Window::~Window() {}

void Window::init() {
    initBackgroundColor();
    initCamera();
    initProjectionMatrix();
    initScene();

    // DELETEME after doing the ui objective
    // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // std::cout << glfwGetInputMode(m_window, GLFW_CURSOR) << std::endl;
}

void Window::initBackgroundColor() {
    glClearColor(0.3, 0.5, 0.7, 1.0);
}

void Window::initCamera() {
    m_camera = std::make_shared<Camera>(
        glm::vec3(5.0f, 2.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
}

void Window::initProjectionMatrix() {
    const float aspect = static_cast<float>(m_framebufferWidth) / static_cast<float>(m_framebufferHeight);
    const float near_plane = 0.2f;
    const float far_plane = 100.0f;

    m_projection = glm::perspective(
        glm::radians(DEFAULT_FOVY),
        aspect,
        NEAR_PLANE,
        FAR_PLANE
    );
}

void Window::initScene() {
    m_scene = std::make_unique<Scene>();
}

void Window::calculateDeltaTime() {
    const float current_frame_time = glfwGetTime();
    m_delta_time = current_frame_time - m_last_frame_time;
    m_last_frame_time = current_frame_time;
}

void Window::appLogic() {
    calculateDeltaTime();

    if (m_shooting) {
        const Ray ray = m_camera->shootRay();
        m_scene->handleShot(ray);

        m_shooting = false;
    }

    m_camera->move(m_input_handler, m_scene->getAllCollidableObjects(), m_delta_time);
    m_scene->tick(m_delta_time);
}

void Window::guiLogic() {
    // DELETEME after doing the ui objective
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // std::cout << glfwGetInputMode(m_window, GLFW_CURSOR) << std::endl;

    ImGuiIO& io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
}

void Window::draw()
{
    glEnable(GL_DEPTH_TEST);


    glm::mat4 world(1.0f);
    glm::mat4 trans = world;

    m_scene->draw(m_projection, m_camera->getView(), m_model);

    CHECK_GL_ERRORS;
}

void Window::cleanup() {}


// EVENT HANDLERS
bool Window::cursorEnterWindowEvent(int entered) {
    return false;
}

bool Window::mouseMoveEvent(double xPos, double yPos) {
    float x_pos = static_cast<float>(xPos);
    float y_pos = static_cast<float>(yPos);
    // std::cout << x_pos << ", " << y_pos << std::endl;
    m_input_handler.updateCursorPos(std::make_pair(x_pos, y_pos));
    m_camera->updateDirection(m_input_handler);

    // this value is not used by the caller in the cs488 framework
    return false;
}

bool Window::mouseButtonInputEvent(int button, int actions, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && actions == GLFW_PRESS) {
        std::cout << "shooting ray" << std::endl;
        m_shooting = true;
    }

    return false;
}

bool Window::mouseScrollEvent(double xOffSet, double yOffSet) {
    return false;
}

bool Window::windowResizeEvent(int width, int height) {
    return false;
}

bool Window::keyInputEvent(int key, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            std::cout << "quitting game..." << std::endl;
            glfwSetWindowShouldClose(m_window, GL_TRUE);
            return true;
        }

        m_input_handler.pressKey(key);
    } else if (action == GLFW_RELEASE) {
        m_input_handler.releaseKey(key);
    }

    return true;
}
