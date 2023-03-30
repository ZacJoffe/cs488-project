#pragma once

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "Camera.h"
#include "Floor.h"
#include "Geometry.h"
#include "InputHandler.h"
#include "ShaderHandler.h"

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
    void initShaderHandler();
    void initFloor();
    void initProjectionMatrix();
    void initCamera();

    void calculateDeltaTime();

    std::shared_ptr<ShaderHandler> m_shader_handler;

    glm::mat4 m_projection;
    // glm::mat4 m_view;
    glm::mat4 m_model;

    std::shared_ptr<Camera> m_camera;

    InputHandler m_input_handler;

    // Fields related to grid geometry.
    GLuint m_grid_vao; // Vertex Array Object
    GLuint m_grid_vbo; // Vertex Buffer Object

    // Matrices controlling the camera and projection.
    glm::mat4 proj;
    glm::mat4 view;

    // std::vector<std::shared_ptr<Geometry>> m_geos;
    std::shared_ptr<Floor> m_floor;

    float m_delta_time;
    float m_last_frame_time;
};
