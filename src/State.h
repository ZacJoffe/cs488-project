#pragma once

#include "GameContext.h"

#include <memory>

// this enum is a hacky way to let one state modify the state of the window
enum class StateValue {
    Menu,
    Game,
};

struct State {
    virtual ~State() {}

    virtual void appLogic(float delta_time) = 0;
    virtual void guiLogic(const std::unique_ptr<GameContext> & game_context) = 0;
    virtual void draw() = 0;
    virtual void handleMouseMove(double xpos, double ypos) = 0;
    virtual void handleMouseButtonInput(int button, int actions, int mods) = 0;
    virtual void handleKeyInput(int key, int action, int mods) = 0;

    virtual bool shouldSwitchStates() = 0;
    virtual bool shouldCloseWindow() = 0;
};

