#pragma once

#include "BoundingBox.h"
#include "Enemy.h"
#include "GameContext.h"
#include "Ray.h"
#include "Rng.h"
#include "ShaderHandler.h"
#include "Skybox.h"
#include "Texture.h"
#include "Tile.h"

#include <array>
#include <glm/glm.hpp>
#include <list>
#include <memory>
#include <vector>

namespace scene_constants {
    // NOTE the world is N x Y x N, where N is passed in to the Scene
    // constructor via the game context
    static const float Y = 5.0f;
    static const float BOUNDING_BOX_OFFSET = 0.2f;
}

class Scene {
public:
    Scene(const GameContext & game_context);

    void draw(const glm::mat4 & projection, const glm::mat4 & view, const glm::mat4 & model) const;
    std::list<BoundingBox> getStaticCollidableObjects() const;
    std::list<BoundingBox> getAllCollidableObjects() const;
    void handleShot(const Ray & ray);
    void tick(float delta_time);
    void respawnEnemies();

private:
    void initSkybox(const std::vector<std::string> & filenames);
    void initFloor(const std::string & texture_filename);
    void initWalls(const std::string & texture_filename);
    void initEnemyTexture(const std::string & texture_filename);
    void initEnemies();

    std::shared_ptr<ShaderHandler> m_shader_handler;

    unsigned int m_world_size;

    std::shared_ptr<Texture> m_floor_texture;
    Tiles m_floor;

    std::shared_ptr<Texture> m_wall_texture;
    std::array<Tiles, 4> m_walls;

    unsigned int m_num_enemies;
    std::shared_ptr<Texture> m_enemy_texture;
    std::list<Enemy> m_enemies;

    std::shared_ptr<ShaderHandler> m_skybox_shader_handler;
    std::unique_ptr<Skybox> m_skybox;

    Rng m_rng;
};

