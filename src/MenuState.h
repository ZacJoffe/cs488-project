#pragma once

#include "GameContext.h"
#include "State.h"
#include "imgui.h"

class MenuState : public State {
public:
    MenuState(int framebuffer_width, int framebuffer_height);
    ~MenuState() override;

    void appLogic(float delta_time) override;
    void guiLogic(const std::unique_ptr<GameContext> & game_context) override;
    void draw() override;
    void handleMouseMove(double xpos, double ypos) override;
    void handleMouseButtonInput(int button, int actions, int mods) override;
    bool handleKeyInput(int key, int action, int mods) override;
    bool switchStates() override;

private:
    bool m_show_root;
    ImFont * m_font_title;
    ImFont * m_font_normal;

    bool m_switch_states;
    int m_framebuffer_width;
    int m_framebuffer_height;
};

