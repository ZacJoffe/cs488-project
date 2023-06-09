#pragma once

#include <map>
#include <string>
#include <vector>

namespace game_context_constants {
    static const unsigned int DEFAULT_NUM_ENEMIES = 5;
    static const unsigned int MIN_NUM_ENEMIES = 2;
    static const unsigned int MAX_NUM_ENEMIES = 10;

    static const unsigned int DEFAULT_WORLD_SIZE = 50;
    static const unsigned int MIN_WORLD_SIZE = 20;
    static const unsigned int MAX_WORLD_SIZE = 75;

    static const unsigned int NUM_FLOOR_TEXTURES = 5;
    static const std::string FLOOR_TEXTURES[NUM_FLOOR_TEXTURES] = {
        "./assets/textures/floor/Grass_02.png",
        "./assets/textures/floor/Grass_01.png",
        "./assets/textures/floor/Grass_03.png",
        "./assets/textures/floor/leaves 1.png",
        "./assets/textures/floor/sand 1.png"
    };

    static const unsigned int NUM_WALL_TEXTURES = 5;
    static const std::string WALL_TEXTURES[NUM_WALL_TEXTURES] = {
        "./assets/textures/wall/stone wall 4.png",
        "./assets/textures/wall/stone wall 2.png",
        "./assets/textures/wall/stone wall 7.png",
        "./assets/textures/wall/paving 4.png",
        "./assets/textures/wall/wood 3.png"
    };

    static const unsigned int NUM_ENEMY_TEXTURES = 5;
    static const std::string ENEMY_TEXTURES[NUM_ENEMY_TEXTURES] = {
        "./assets/textures/enemy/stone 2.png",
        "./assets/textures/enemy/stone 1.png",
        "./assets/textures/enemy/stone 3.png",
        "./assets/textures/enemy/snow 1.png",
        "./assets/textures/enemy/fire.png"
    };

    static const unsigned int NUM_SKYBOXES = 3;
    static const std::vector<std::string> SKYBOXES[NUM_SKYBOXES] = {
        { // storm
            "./assets/textures/skybox/stormydays/stormydays_ft.tga", // right
            "./assets/textures/skybox/stormydays/stormydays_bk.tga", // left
            "./assets/textures/skybox/stormydays/stormydays_up.tga", // top
            "./assets/textures/skybox/stormydays/stormydays_dn.tga", // bottom
            "./assets/textures/skybox/stormydays/stormydays_rt.tga", // back
            "./assets/textures/skybox/stormydays/stormydays_lf.tga"  // front
        },
        { // teal
            "./assets/textures/skybox/teal1/0003.jpg", // right
            "./assets/textures/skybox/teal1/0005.jpg", // left
            "./assets/textures/skybox/teal1/0006.jpg", // top
            "./assets/textures/skybox/teal1/0001.jpg", // bottom
            "./assets/textures/skybox/teal1/0002.jpg", // front
            "./assets/textures/skybox/teal1/0004.jpg"  // back
        },
        { // cloudy
            "./assets/textures/skybox/miramar/miramar_ft.tga", // right
            "./assets/textures/skybox/miramar/miramar_bk.tga", // left
            "./assets/textures/skybox/miramar/miramar_up.tga", // top
            "./assets/textures/skybox/miramar/miramar_dn.tga", // bottom
            "./assets/textures/skybox/miramar/miramar_rt.tga", // back
            "./assets/textures/skybox/miramar/miramar_lf.tga"  // front
        }
    };
}

struct GameContext {
    unsigned int num_enemies;
    unsigned int world_size;
    int floor_texture;
    int wall_texture;
    int enemy_texture;
    int skybox;
    GameContext() :
        num_enemies(game_context_constants::DEFAULT_NUM_ENEMIES),
        world_size(game_context_constants::DEFAULT_WORLD_SIZE),
        floor_texture(0),
        wall_texture(0),
        enemy_texture(0),
        skybox(0) {}
};

