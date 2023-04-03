#pragma once

#include "cs488-framework/CS488Window.hpp"
#include "State.h"

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
    // void setState(const StateValue & state_value);
    void switchToGameState();
    void calculateDeltaTime();

    StateValue m_state_value;
    std::unique_ptr<State> m_state;

    float m_delta_time;
    float m_last_frame_time;
};

