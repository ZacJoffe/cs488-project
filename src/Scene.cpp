#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>
#include <utility>

using namespace scene_constants;

Scene::Scene(unsigned int num_enemies) {
    // init shader handler
    m_shader_handler = std::make_shared<ShaderHandler>();
    for (unsigned int i = 0; i < num_enemies; ++i) {
        m_enemies.emplace_back(
            m_shader_handler,
            // randomly generate coordinates between (2, 2) and (N - 2, N - 2)
            glm::vec3((N - 4.0f) * m_rng() + 2.0f, 2.0f, (N - 4.0f) * m_rng() + 2.0f),
            "./assets/meshes/sphere.obj"
        );
    }


    initFloor();
    initWalls();
}

void Scene::draw(const glm::mat4 & projection, const glm::mat4 & view, const glm::mat4 & model) const {
    m_shader_handler->enable();

    m_shader_handler->uploadProjectionUniform(projection);
    m_shader_handler->uploadViewUniform(view);
    m_shader_handler->uploadModelUniform(model);

    m_floor.draw();

    for (const auto & wall : m_walls) {
        wall.draw();
    }

    for (const auto & enemy : m_enemies) {
        enemy.draw();
    }

    m_shader_handler->disable();
    glBindVertexArray(0);
}

std::list<BoundingBox> Scene::getStaticCollidableObjects() const {
    return {
        *m_walls[0].getBoundingBox(),
        *m_walls[1].getBoundingBox(),
        *m_walls[2].getBoundingBox(),
        *m_walls[3].getBoundingBox()
    };
}

std::list<BoundingBox> Scene::getAllCollidableObjects() const {
    // walls + enemies
    std::list<BoundingBox> bounding_boxes = getStaticCollidableObjects();
    for (const auto & enemy : m_enemies) {
        bounding_boxes.push_back(enemy.getBoundingBox());
    }

    return bounding_boxes;
}

void Scene::handleShot(const Ray & ray) {
    // the ray can shoot through enemies and kill multiple of them, thus we
    // don't need intersection points (t values) and must iterate through each
    // alive enemy
    for (auto & enemy : m_enemies) {
        const bool hit = enemy.collisionTestXZ(ray);
        if (hit) {
            // NOTE this tests dead enemies, but the kill method does nothing if
            // the enemy is already dead
            std::cout << "hit enemy " + enemy.getId() << std::endl;
            enemy.kill();
        }
    }
}

void Scene::tick(float delta_time) {
    for (auto & enemy : m_enemies) {
        enemy.move(getStaticCollidableObjects(), delta_time);
    }
}

void Scene::initFloor() {
    m_floor_texture = std::make_shared<Texture>("./assets/textures/Grass_02.png");
    m_floor = Tiles(
        glm::mat4(1.0f),
        WORLD_BOUNDARY_MAX.x,
        WORLD_BOUNDARY_MAX.z,
        m_shader_handler,
        m_floor_texture,
        nullptr
    );

}

void Scene::initWalls() {
    m_wall_texture = std::make_shared<Texture>("./assets/textures/stone wall 4.png");

    /*
    2D (x-z plane) diagram of scene
               top
    ^    tl +--------+ tr
    |       +        +
    |       +        +
    |       +        +
    |  left +        + right
    |       +        +
    |       +        +
    |       +        +
    |       +        +
    |    bl +--------+ br
    |         bottom
    x
     z-------------------->
    */

    // this is pretty messy, but it seems to work!
    // left wall bl -> tl (0, 0 -> N, 0)
    glm::mat4 trans = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, -N));
    m_walls[0] = Tiles(
        glm::translate(trans, glm::vec3(0.0f, 0.0f, N - WORLD_BOUNDARY_MAX.y)),
        WORLD_BOUNDARY_MAX.x,
        WORLD_BOUNDARY_MAX.y,
        m_shader_handler,
        m_wall_texture,
        std::make_shared<BoundingBox>(glm::vec2(-BOUNDING_BOX_OFFSET, -BOUNDING_BOX_OFFSET), glm::vec2(N + BOUNDING_BOX_OFFSET, BOUNDING_BOX_OFFSET))
    );

    // top wall tl -> tr (N, 0 -> N, N)
    trans = glm::translate(trans, glm::vec3(N, 0.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_walls[1] = Tiles(
        glm::translate(trans, glm::vec3(0.0f, 0.0f, N - WORLD_BOUNDARY_MAX.y)),
        50,
        10,
        m_shader_handler,
        m_wall_texture,
        std::make_shared<BoundingBox>(glm::vec2(N - BOUNDING_BOX_OFFSET, -BOUNDING_BOX_OFFSET), glm::vec2(N + BOUNDING_BOX_OFFSET, N + BOUNDING_BOX_OFFSET))
    );

    // right wall br -> tr (0, N -> N, N)
    trans = glm::translate(trans, glm::vec3(N, 0.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_walls[2] = Tiles(
        glm::translate(trans, glm::vec3(0.0f, 0.0f, N - WORLD_BOUNDARY_MAX.y)),
        50,
        10,
        m_shader_handler,
        m_wall_texture,
        std::make_shared<BoundingBox>(glm::vec2(-BOUNDING_BOX_OFFSET, N - BOUNDING_BOX_OFFSET), glm::vec2(N + BOUNDING_BOX_OFFSET, N + BOUNDING_BOX_OFFSET))
    );

    // bottom wall bl -> br (0, 0 -> 0, N)
    trans = glm::translate(trans, glm::vec3(N, 0.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_walls[3] = Tiles(
        glm::translate(trans, glm::vec3(0.0f, 0.0f, N - WORLD_BOUNDARY_MAX.y)),
        50,
        10,
        m_shader_handler,
        m_wall_texture,
        std::make_shared<BoundingBox>(glm::vec2(-BOUNDING_BOX_OFFSET, -BOUNDING_BOX_OFFSET), glm::vec2(BOUNDING_BOX_OFFSET, N + BOUNDING_BOX_OFFSET))
    );
}

