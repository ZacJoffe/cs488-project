#include "Window.h"
#include "Camera.h"
#include "GLFW/glfw3.h"
#include "cs488-framework/GlErrorCheck.hpp"
#include "Tile.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <utility>

using namespace window_constants;

Window::Window() :
    m_input_handler(m_windowHeight, m_windowWidth),
    m_delta_time(0.0f),
    m_last_frame_time(0.0f) {}

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

    m_input_handler.setCamera(m_camera);
}

void Window::initProjectionMatrix() {
    const float aspect = static_cast<float>(m_framebufferWidth) / static_cast<float>(m_framebufferHeight);
    // TODO these values probably need tweaking (including fovy)
    const float near_plane = 1.0f;
    const float far_plane = 100.0f;

    m_projection = glm::perspective(
        glm::radians(DEFAULT_FOVY),
        aspect,
        near_plane,
        far_plane
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

    m_input_handler.performActions(m_delta_time);
}

void Window::guiLogic() {
    // DELETEME after doing the ui objective
    // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // std::cout << glfwGetInputMode(m_window, GLFW_CURSOR) << std::endl;
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

    // this value is not used by the caller in the cs488 framework
    return false;
}

bool Window::mouseButtonInputEvent(int button, int actions, int mods) {
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
