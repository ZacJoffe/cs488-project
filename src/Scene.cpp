#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

Scene::Scene() {
    // init shader handler
    m_shader_handler = std::make_shared<ShaderHandler>();

    initFloor();
    initWalls();
}

void Scene::draw(const glm::mat4 & projection, const glm::mat4 & view, const glm::mat4 & model) {
    m_shader_handler->enable();

    m_shader_handler->uploadProjectionUniform(projection);
    m_shader_handler->uploadViewUniform(view);
    m_shader_handler->uploadModelUniform(model);

    m_floor.draw();

    for (const auto & wall : m_walls) {
        wall.draw();
    }

    m_shader_handler->disable();
    glBindVertexArray(0);
}

void Scene::initFloor() {
    m_floor_texture = std::make_shared<Texture>("./assets/textures/Grass_02.png");
    m_floor = Tiles(
        glm::mat4(1.0f),
        50,
        50,
        m_shader_handler,
        m_floor_texture
    );

}

void Scene::initWalls() {
    m_wall_texture = std::make_shared<Texture>("./assets/textures/stone wall 4.png");

    // this is pretty messy, but it seems to work!
    glm::mat4 trans = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, -50.0f));
    m_walls[0] = Tiles(
        glm::translate(trans, glm::vec3(0.0f, 0.0f, 40.0f)),
        50,
        10,
        m_shader_handler,
        m_wall_texture
    );

    trans = glm::translate(trans, glm::vec3(50.f, 0.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_walls[1] = Tiles(
        glm::translate(trans, glm::vec3(0.0f, 0.0f, 40.0f)),
        50,
        10,
        m_shader_handler,
        m_wall_texture
    );

    trans = glm::translate(trans, glm::vec3(50.f, 0.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_walls[2] = Tiles(
        glm::translate(trans, glm::vec3(0.0f, 0.0f, 40.0f)),
        50,
        10,
        m_shader_handler,
        m_wall_texture
    );

    trans = glm::translate(trans, glm::vec3(50.f, 0.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_walls[3] = Tiles(
        glm::translate(trans, glm::vec3(0.0f, 0.0f, 40.0f)),
        50,
        10,
        m_shader_handler,
        m_wall_texture
    );
}
