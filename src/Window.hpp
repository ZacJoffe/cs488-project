#pragma once

#include <glm/glm.hpp>

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"

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
    void initFloor();
    void initProjectionMatrix();
    void initViewMatrix();

    void uploadCommonSceneUniforms();

    // Fields related to the shader and uniforms.
    ShaderProgram m_shader;
    // GLint P_uni; // Uniform location for Projection matrix.
    // GLint V_uni; // Uniform location for View matrix.
    // GLint M_uni; // Uniform location for Model matrix.

    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_model;

    // Fields related to grid geometry.
    GLuint m_grid_vao; // Vertex Array Object
    GLuint m_grid_vbo; // Vertex Buffer Object

    // Matrices controlling the camera and projection.
    glm::mat4 proj;
    glm::mat4 view;

    // TODO DELETEME
    // float colour[3];
    // int current_col;
};
