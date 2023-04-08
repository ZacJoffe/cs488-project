#include "Window.h"

#include <gl3w/GL/gl3w.h>
#include "GameState.h"
#include "MenuState.h"
#include "State.h"

#include <imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <iostream>
#include <memory>
#include <pmmintrin.h>
#include <stdexcept>

Window & Window::getInstance() {
    static Window window;
    return window;
}

Window::Window() :
    m_delta_time(0.0f),
    m_last_frame_time(0.0f),
    m_curr_state_value(StateValue::Menu) {}

void Window::launch(int width, int height, const std::string & title, float fps) {
    run(width, height, title, fps);
}

void Window::run(int width, int height, const std::string & window_title, float target_fps) {
    m_window_width = width;
    m_window_height = height;
    m_window_title = window_title;

    glfwSetErrorCallback([](int error, const char * description){
        std::cout << "GLFW Error Code: " << error << std::endl
                  << "GLFW Eror Description: " << description << std::endl;
    });

    if (!glfwInit()) {
        throw std::runtime_error("Failed to init glfw");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);

    // m_monitor = glfwGetPrimaryMonitor();
    // if (!m_monitor) {
    //     glfwTerminate();
    //     throw std::runtime_error("Failed to get primary monitor");
    // }

    m_window = glfwCreateWindow(m_window_width, m_window_height, m_window_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create glfw window");
    }

    glfwGetFramebufferSize(m_window, &m_framebuffer_width, &m_framebuffer_height);
    glfwMakeContextCurrent(m_window);

    // TODO update gl3w
    gl3wInit();
    if (!gl3wIsSupported(3, 3)) {
        throw std::runtime_error("OpenGL not supported");
    }

    const auto gl_version = glGetString(GL_VERSION);
    const auto glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "OpenGL " << gl_version << ", GLSL " << glsl_version << std::endl;

    register_glfw_callbacks();

    // TODO refactor into method
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    // ImGui_ImplOpenGL3_Init(glsl_version); // FIXME
    ImGui_ImplOpenGL3_Init("#version 130");

    windowResizeEvent(width, height);

    while (glGetError()) {}

    try {
        glfwSwapInterval(1);

        // TODO
        init();

        while (!glfwWindowShouldClose(m_window)) {
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            appLogic();
            guiLogic();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            draw();

            glfwGetFramebufferSize(m_window, &m_framebuffer_width, &m_framebuffer_height);
            glViewport(0, 0, m_framebuffer_width, m_framebuffer_height);
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(m_window);
        }
    } catch (const std::exception & e) {
        std::cerr << "Exception thrown: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Uncaught exception thrown! Terminating..." << std::endl;
    }

    glfwDestroyWindow(m_window);
}


void Window::register_glfw_callbacks() {
    glfwSetKeyCallback(m_window, [](GLFWwindow * window, int key, int scancode, int action, int mods) {
        getInstance().keyInputEvent(key, action, mods);
    });
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow * window, int width, int height) {
        getInstance().windowResizeEvent(width, height);
    });
    // glfwSetScrollCallback(m_window, [](GLFWwindow * window, double xoffset, double yoffset) {
    //     getInstance().mouseScrollEvent(xoffset, yoffset);
    // });
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow * window, int button, int action, int mods) {
        getInstance().mouseButtonInputEvent(button, action, mods);
    });
    glfwSetCursorPosCallback(m_window, [](GLFWwindow * window, double xpos, double ypos) {
        getInstance().cursorPositionEvent(xpos, ypos);
    });
    // glfwSetCursorEnterCallback(m_window, [](GLFWwindow * window, int entered) {
    //     getInstance().cursorEnterWindowEvent(entered);
    // })
}

void Window::init() {
    ImGuiIO & io = ImGui::GetIO();
    m_font_title = io.Fonts->AddFontFromFileTTF("./assets/fonts/roboto/Roboto-Regular.ttf", 48);
    m_font_normal = io.Fonts->AddFontFromFileTTF("./assets/fonts/roboto/Roboto-Regular.ttf", 16);

    // always start in menu state
    m_curr_state = std::make_unique<MenuState>(m_framebuffer_width, m_framebuffer_height, m_font_title, m_font_normal);
    m_game_context = std::make_unique<GameContext>();
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::appLogic() {
    if (m_curr_state->shouldCloseWindow()) {
        glfwSetWindowShouldClose(m_window, GL_TRUE);
        return;
    }

    if (m_curr_state->shouldSwitchStates()) {
        toggleState();
        return;
    }

    calculateDeltaTime();

    m_curr_state->appLogic(m_delta_time);
}

void Window::guiLogic() {
    m_curr_state->guiLogic(m_game_context);
}

void Window::draw() {
    m_curr_state->draw();
}

// void Window::cleanup() {}


// EVENT HANDLERS
void Window::cursorPositionEvent(double xpos, double ypos) {
    m_curr_state->handleMouseMove(xpos, ypos);
}

void Window::mouseButtonInputEvent(int button, int action, int mods) {
    m_curr_state->handleMouseButtonInput(button, action, mods);
}

void Window::windowResizeEvent(int width, int height) {
    m_window_width = width;
    m_window_height = height;
}

void Window::keyInputEvent(int key, int action, int mods) {
    m_curr_state->handleKeyInput(key, action, mods);
}

void Window::toggleState() {
    switch (m_curr_state_value) {
        case StateValue::Menu: {
            std::cout << "switching to game state" << std::endl;

            m_curr_state_value = StateValue::Game;
            m_curr_state = std::make_unique<GameState>(*m_game_context, m_framebuffer_width, m_framebuffer_height);
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        }
        case StateValue::Game: {
            std::cout << "switching to game state" << std::endl;

            m_curr_state_value = StateValue::Menu;
            m_curr_state = std::make_unique<MenuState>(m_framebuffer_width, m_framebuffer_height, m_font_title, m_font_normal);
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

