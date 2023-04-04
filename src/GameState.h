#pragma once

#include "State.h"

#include "cs488-framework/OpenGLImport.hpp"
#include "Camera.h"
#include "GameContext.h"
#include "InputHandler.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include <memory>

#include <soloud.h>
#include <soloud_wav.h>

namespace game_state_constants {
    static const float DEFAULT_FOVY = 60.0f;
    static const float NEAR_PLANE = 0.2f;
    static const float FAR_PLANE = 100.0f;
}

class GameState : public State {
public:
    GameState(const GameContext & game_context, int framebuffer_width, int framebuffer_height);
    ~GameState() override;

    void appLogic(float delta_time) override;
    void guiLogic(const std::unique_ptr<GameContext> & game_context) override;
    void draw() override;
    void handleMouseMove(double xpos, double ypos) override;
    void handleMouseButtonInput(int button, int actions, int mods) override;
    bool handleKeyInput(int key, int action, int mods) override;
    bool switchStates() override;

private:
    void initCamera();
    void initProjectionMatrix(int framebuffer_width, int framebuffer_height);
    void initScene(const GameContext & game_context);
    void initSoundFiles();

    std::shared_ptr<Camera> m_camera; // encapsulates the view matrix
    glm::mat4 m_projection;
    glm::mat4 m_model;

    InputHandler m_input_handler;

    std::unique_ptr<Scene> m_scene;

    SoLoud::Wav m_gunshot_wav;

    bool m_shooting;
};

