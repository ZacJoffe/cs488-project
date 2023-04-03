#pragma once

struct State {
    virtual ~State() {}

    virtual void appLogic(float delta_time) = 0;
    virtual void guiLogic() = 0;
    virtual void draw() = 0;
    virtual void handleMouseMove(double xpos, double ypos) = 0;
    virtual void handleMouseButtonInput(int button, int actions, int mods) = 0;
    virtual bool handleKeyInput(int key, int action, int mods) = 0;
};

