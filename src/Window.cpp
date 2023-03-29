#include "Window.hpp"
#include "Camera.hpp"
#include "GLFW/glfw3.h"
#include "cs488-framework/GlErrorCheck.hpp"
#include "Floor.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace window_constants;

Window::Window() {}
Window::~Window() {}

void Window::init() {
    initBackgroundColor();
    initShaderHandler();
    initFloor();
    initCamera();
    initProjectionMatrix();

    m_model = glm::mat4(1.0f);
}

void Window::initBackgroundColor() {
    glClearColor(0.3, 0.5, 0.7, 1.0);
}

void Window::initShaderHandler() {
    m_shader_handler = std::make_shared<ShaderHandler>();
}

void Window::initFloor() {
    m_geos.push_back(std::make_shared<Floor>(m_shader_handler));
}

void Window::initProjectionMatrix() {
    float aspect = static_cast<float>(m_framebufferWidth) / static_cast<float>(m_framebufferHeight);
    // TODO these values probably need tweaking (including fovy)
    float near_plane = 1.0f;
    float far_plane = 100.0f;

    m_projection = glm::perspective(
        glm::radians(DEFAULT_FOVY),
        aspect,
        near_plane,
        far_plane
    );
}

void Window::initCamera() {
    m_camera = Camera(
        // glm::vec3(0.0f, 1.0f, 1.0f),
        // glm::vec3(0.0f, 0.0f, 0.0f),
        // glm::vec3(0.0f, 1.0f, 0.0f)
        glm::vec3(0.0f, 1.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
}

void Window::appLogic() {
    m_key_input_handler.performAction(m_camera);
}

void Window::guiLogic() {}

void Window::draw()
{
    glEnable(GL_DEPTH_TEST);

    // glm::mat4 W(1.0f);
    // W = glm::rotate(W, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // m_model = W * m_model;


    m_shader_handler->uploadProjectionUniform(m_projection);
    m_shader_handler->uploadViewUniform(m_camera.getView());
    m_shader_handler->uploadModelUniform(m_model);

    for (const auto geo : m_geos) {
        geo->draw();
    }

    glBindVertexArray(0);
    CHECK_GL_ERRORS;

    /*
    // Create a global transformation for the model (centre it).
    mat4 W;
    W = glm::translate( W, vec3( -float(DIM)/2.0f, 0, -float(DIM)/2.0f ) );

    m_shader.enable();
        glEnable( GL_DEPTH_TEST );

        glUniformMatrix4fv( P_uni, 1, GL_FALSE, value_ptr( proj ) );
        glUniformMatrix4fv( V_uni, 1, GL_FALSE, value_ptr( view ) );
        glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( W ) );

        // Just draw the grid for now.
        glBindVertexArray( m_grid_vao );
        glUniform3f( col_uni, 1, 1, 1 );
        glDrawArrays( GL_LINES, 0, (3+DIM)*4 );

        // Draw the cubes
        // Highlight the active square.
    m_shader.disable();

    // Restore defaults
    glBindVertexArray( 0 );

    CHECK_GL_ERRORS;
    */
}

void Window::cleanup() {}


// EVENT HANDLERS
bool Window::cursorEnterWindowEvent(int entered) {
    return false;
}

bool Window::mouseMoveEvent(double xPos, double yPos) {
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

        m_key_input_handler.pressKey(key);
    } else if (action == GLFW_RELEASE) {
        m_key_input_handler.releaseKey(key);
    }

    return true;
}
