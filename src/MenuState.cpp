#include "MenuState.h"
#include <gl3w/GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

#include <iostream>

MenuState::MenuState() : m_show_root(true), m_switch_states(false) {
    ImGuiIO & io = ImGui::GetIO();
    m_font_title = io.Fonts->AddFontFromFileTTF("./assets/fonts/roboto/Roboto-Regular.ttf", 36);
    m_font_normal = io.Fonts->AddFontFromFileTTF("./assets/fonts/roboto/Roboto-Regular.ttf", 12);

    glClearColor(0.3, 0.5, 0.7, 1.0);
}

MenuState::~MenuState() {}

void MenuState::appLogic(float delta_time) {}

void MenuState::guiLogic() {
    if (m_show_root) {
        ImGui::Begin("Root", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::PushFont(m_font_title);
        ImGui::Text("Codename: Kefka");
        ImGui::PopFont();

        ImGui::PushFont(m_font_normal);
        if (ImGui::Button("Start Game")) {
            std::cout << "start game button pressed" << std::endl;
            m_switch_states = true;
        }
        ImGui::PopFont();

        ImGui::End();
    }
}

void MenuState::draw() {}

void MenuState::handleMouseMove(double xpos, double ypos) {}

void MenuState::handleMouseButtonInput(int button, int actions, int mods) {}

bool MenuState::handleKeyInput(int key, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            std::cout << "quitting game..." << std::endl;
            return true;
        }

        // this is mostly here for quicker debugging/testing
        if (key == GLFW_KEY_S) {
            m_switch_states = true;
        }
    }

    return false;
}

bool MenuState::switchStates() {
    return m_switch_states;
}

