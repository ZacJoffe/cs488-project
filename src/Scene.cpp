#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

Scene::Scene() {
    // init shader handler
    m_shader_handler = std::make_shared<ShaderHandler>();

    // init floor tiles
    m_floor_texture = std::make_shared<Texture>("./assets/textures/Grass_02.png");
    m_floor = Tiles(
        glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.5f)),
        50,
        50,
        m_shader_handler,
        m_floor_texture
    );
}

void Scene::draw(const glm::mat4 & projection, const glm::mat4 & view, const glm::mat4 & model) {
    m_shader_handler->enable();

    m_shader_handler->uploadProjectionUniform(projection);
    m_shader_handler->uploadViewUniform(view);
    m_shader_handler->uploadModelUniform(model);

    m_floor.draw();

    m_shader_handler->disable();
    glBindVertexArray(0);
}

