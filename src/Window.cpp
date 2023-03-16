// Termm--Fall 2020

#include "cs488-framework/GlErrorCheck.hpp"

#include "Window.hpp"

// #include <sys/types.h>
// #include <unistd.h>

#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

#include <iostream>

static const float DEFAULT_FOVY = 45.0f;

Window::Window() {}
Window::~Window() {}

void Window::init() {
    // Set the background colour.
    glClearColor(0.3, 0.5, 0.7, 1.0);

    // Build the shader
    m_shader.generateProgramObject();
    m_shader.attachVertexShader(getAssetFilePath("VertexShader.vs").c_str());
    m_shader.attachFragmentShader(getAssetFilePath("FragmentShader.fs").c_str());
    m_shader.link();

    // Set up the uniforms
    P_uni = m_shader.getUniformLocation("P");
    // TODO encapsulate
    V_uni = m_shader.getUniformLocation("V");
    M_uni = m_shader.getUniformLocation("M");

    initFloor();

    // Set up initial view and projection matrices (need to do this here,
    // since it depends on the GLFW window being set up correctly).
    view = glm::lookAt(
        glm::vec3(0.0f, 2.*float(DIM)*2.0*M_SQRT1_2, float(DIM)*2.0*M_SQRT1_2),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    proj = glm::perspective(
        glm::radians(30.0f),
        float(m_framebufferWidth) / float(m_framebufferHeight),
        1.0f, 1000.0f
    );
}

void Window::initFloor() {
    // TODO
}

void Window::initProjectionMatrix() {
    float aspect = static_cast<float>(m_framebufferWidth) / static_cast<float>(m_framebufferHeight);
    // TODO these values probably need tweaking (including fovy)
    float near_plane = 1.0f;
    float far_plane = 1000.0f;

    m_projection = glm::perspective(
        glm::radians(DEFAULT_FOVY),
        aspect,
        near_plane,
        far_plane,
    );
}

void Window::initViewMatrix() {
    // TODO here
}


void Window::uploadCommonSceneUniforms() {
    // TODO
}

void Window::appLogic() {}

void Window::guiLogic() {}

void Window::draw()
{
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
    bool eventHandled(false);

    if( action == GLFW_PRESS ) {
        // Respond to some key events.
    }

    return eventHandled;
}
