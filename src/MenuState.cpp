#include "MenuState.h"
#include <gl3w/GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "GameContext.h"
#include "imgui.h"

#include <iostream>

MenuState::MenuState(int framebuffer_width,
                     int framebuffer_height,
                     ImFont * const font_title,
                     ImFont * const font_normal) :
    m_show_root(true),
    m_switch_states(false),
    m_close_window(false),
    m_framebuffer_width(framebuffer_width),
    m_framebuffer_height(framebuffer_height),
    m_font_title(font_title),
    m_font_normal(font_normal)
{
    glClearColor(0.3, 0.5, 0.7, 1.0);
}

MenuState::~MenuState() {}

void MenuState::appLogic(float delta_time) {}

void MenuState::guiLogic(const std::unique_ptr<GameContext> & game_context) {
    if (m_show_root) {
        ImGui::Begin("Root", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowSize(ImVec2(0, 0));
        // center on screen
        ImGui::SetWindowPos(
            ImVec2(
                m_framebuffer_width * 0.5f - ImGui::GetWindowWidth() * 0.5f,
                m_framebuffer_height * 0.5f - ImGui::GetWindowHeight() * 0.5f
            )
        );
        ImGui::PushFont(m_font_title);
        ImGui::Text("Kefka: CS488 Project");
        ImGui::PopFont();

        ImGui::PushFont(m_font_normal);
        if (ImGui::Button("Start Game")) {
            std::cout << "start game button pressed" << std::endl;
            m_switch_states = true;
        }
        ImGui::PopFont();

        ImGui::PushFont(m_font_normal);
        if (ImGui::Button("Options")) {
            m_show_root = false;
        }
        ImGui::PopFont();

        ImGui::End();
    } else {
        ImGui::Begin("Root", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowSize(ImVec2(0, 0));
        // center on screen
        ImGui::SetWindowPos(
            ImVec2(
                m_framebuffer_width * 0.5f - ImGui::GetWindowWidth() * 0.5f,
                m_framebuffer_height * 0.5f - ImGui::GetWindowHeight() * 0.5f
            )
        );
        ImGui::PushFont(m_font_normal);
        ImGui::SliderScalar("World Size", ImGuiDataType_U32, &game_context->world_size, &game_context_constants::MIN_WORLD_SIZE, &game_context_constants::MAX_WORLD_SIZE);
        ImGui::SliderScalar("Num Enemies", ImGuiDataType_U32, &game_context->num_enemies, &game_context_constants::MIN_NUM_ENEMIES, &game_context_constants::MAX_NUM_ENEMIES);

        const char * floor_textures[] = { "Grass 1", "Grass 2", "Grass 3", "Leaves", "Sand" };
        ImGui::ListBox("Floor Texture", &game_context->floor_texture, floor_textures, game_context_constants::NUM_FLOOR_TEXTURES, game_context_constants::NUM_FLOOR_TEXTURES);

        const char * wall_textures[] = { "Stone 1", "Stone 2", "Stone 3", "Paving", "Wood" };
        ImGui::ListBox("Wall Texture", &game_context->wall_texture, wall_textures, game_context_constants::NUM_WALL_TEXTURES, game_context_constants::NUM_WALL_TEXTURES);

        const char * enemy_textures[] = { "Mayahem 1", "Mayahem 2", "Mayahem 3", "Snowball", "Fireball" };
        ImGui::ListBox("Enemy Texture", &game_context->enemy_texture, enemy_textures, game_context_constants::NUM_ENEMY_TEXTURES, game_context_constants::NUM_ENEMY_TEXTURES);

        const char * skyboxes[] = { "Storm", "The Void", "Cloudy" };
        ImGui::ListBox("Skybox", &game_context->skybox, skyboxes, game_context_constants::NUM_SKYBOXES, game_context_constants::NUM_SKYBOXES);

        if (ImGui::Button("Back to Main Menu")) {
            m_show_root = true;
        }
        ImGui::PopFont();

        ImGui::End();
    }
}

void MenuState::draw() {}

void MenuState::handleMouseMove(double xpos, double ypos) {}

void MenuState::handleMouseButtonInput(int button, int actions, int mods) {}

void MenuState::handleKeyInput(int key, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            std::cout << "quitting game..." << std::endl;
            m_close_window = true;
            return;
        }

        // this is mostly here for quicker debugging/testing
        if (key == GLFW_KEY_S) {
            m_switch_states = true;
        }
    }
}

bool MenuState::shouldSwitchStates() {
    return m_switch_states;
}

bool MenuState::shouldCloseWindow() {
    return m_close_window;
}

