#pragma once

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "Camera.h"
#include "InputHandler.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace window_constants {
    static const float DEFAULT_FOVY = 60.0f;
}

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
    void initBackgroundColor();
    void initCamera();
    void initProjectionMatrix();
    void initScene();

    void calculateDeltaTime();

    std::shared_ptr<Camera> m_camera; // encapsulates the view matrix
    glm::mat4 m_projection;
    glm::mat4 m_model; // TODO delete?

    InputHandler m_input_handler;

    // std::shared_ptr<Tile> m_floor;
    std::unique_ptr<Scene> m_scene;

    float m_delta_time;
    float m_last_frame_time;
};
