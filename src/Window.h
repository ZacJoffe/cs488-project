#pragma once

#include "cs488-framework/CS488Window.hpp"
#include "GameContext.h"
#include "GameState.h"
#include "MenuState.h"
#include "State.h"
#include "imgui.h"

#include <memory>

class Window : public CS488Window {
public:
    Window();
    virtual ~Window();

protected:
    void init() override;
    void appLogic() override;
    void guiLogic() override;
    void draw() override;
    void cleanup() override;

    bool cursorEnterWindowEvent(int entered) override;
    bool mouseMoveEvent(double xPos, double yPos) override;
    bool mouseButtonInputEvent(int button, int actions, int mods) override;
    bool mouseScrollEvent(double xOffSet, double yOffSet) override;
    bool windowResizeEvent(int width, int height) override;
    bool keyInputEvent(int key, int action, int mods) override;

private:
    void toggleState();
    void calculateDeltaTime();

    StateValue m_curr_state_value;
    std::unique_ptr<State> m_curr_state;
    // std::shared_ptr<MenuState> m_menu_state;
    // std::shared_ptr<GameState> m_game_state;
    std::unique_ptr<GameContext> m_game_context;

    ImFont * m_font_title;
    ImFont * m_font_normal;

    float m_delta_time;
    float m_last_frame_time;
};

