#include "GameState.h"

#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/GlErrorCheck.hpp"
#include "SoundEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace game_state_constants;

GameState::GameState(const GameContext & game_context, int framebuffer_width, int framebuffer_height) : m_shooting(false) {
    initCamera();
    initProjectionMatrix(framebuffer_width, framebuffer_height);
    initScene(game_context);
    initSoundFiles();
}

GameState::~GameState() {}

void GameState::appLogic(float delta_time) {
    if (m_shooting) {
        const Ray ray = m_camera->shootRay();
        m_scene->handleShot(ray);

        m_shooting = false;
    }

    if (m_input_handler.respawnEnemies()) {
        m_scene->respawnEnemies();
    }

    m_camera->move(delta_time, m_input_handler, m_scene->getAllCollidableObjects());
    m_scene->tick(delta_time);
}

void GameState::guiLogic(const std::unique_ptr<GameContext> & game_context) {}

void GameState::draw() {
    glEnable(GL_DEPTH_TEST);

    glm::mat4 world(1.0f);
    glm::mat4 trans = world;
    m_scene->draw(m_projection, m_camera->getView(), m_model);

    CHECK_GL_ERRORS;
}

void GameState::handleMouseMove(double xpos, double ypos) {
    float x_pos = static_cast<float>(xpos);
    float y_pos = static_cast<float>(ypos);

    // std::cout << x_pos << ", " << y_pos << std::endl;
    m_input_handler.updateCursorPos(std::make_pair(x_pos, y_pos));
    m_camera->updateDirection(m_input_handler);
}

void GameState::handleMouseButtonInput(int button, int actions, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && actions == GLFW_PRESS) {
        std::cout << "shooting ray" << std::endl;
        m_shooting = true;

        SoundEngine & sound_engine = SoundEngine::getInstance();
        sound_engine.play(m_gunshot_wav);
    }
}

bool GameState::handleKeyInput(int key, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            std::cout << "quitting game..." << std::endl;
            return true;
        }

        m_input_handler.pressKey(key);
    } else if (action == GLFW_RELEASE) {
        m_input_handler.releaseKey(key);
    }

    return false;
}

void GameState::initCamera() {
    m_camera = std::make_shared<Camera>(
        glm::vec3(5.0f, 2.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    // HACK init the direction of the camera here
    m_camera->updateDirection(m_input_handler);
}

void GameState::initProjectionMatrix(int framebuffer_width, int framebuffer_height) {
    const float aspect = static_cast<float>(framebuffer_width) / static_cast<float>(framebuffer_height);
    const float near_plane = 0.2f;
    const float far_plane = 100.0f;

    m_projection = glm::perspective(
        glm::radians(DEFAULT_FOVY),
        aspect,
        NEAR_PLANE,
        FAR_PLANE
    );
}

void GameState::initScene(const GameContext & game_context) {
    m_scene = std::make_unique<Scene>(game_context);
}

void GameState::initSoundFiles() {
    m_gunshot_wav.load("./assets/sounds/gunshot.wav");
}

bool GameState::switchStates() {
    return false;
}

