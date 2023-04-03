#pragma once

#include "State.h"
#include "imgui.h"

#include <memory>

class MenuState : public State {
public:
    MenuState();
    ~MenuState() override;

    void appLogic(float delta_time) override;
    void guiLogic() override;
    void draw() override;
    void handleMouseMove(double xpos, double ypos) override;
    void handleMouseButtonInput(int button, int actions, int mods) override;
    bool handleKeyInput(int key, int action, int mods) override;
    bool switchStates() override;

private:
    bool m_show_root;
    // std::unique_ptr<ImFont> m_font_title;
    // std::unique_ptr<ImFont> m_font_normal;
    ImFont * m_font_title;
    ImFont * m_font_normal;

    bool m_switch_states;
};

