# CS488 Project
A first-person shooter game engine written for the [CS488](https://student.cs.uwaterloo.ca/~cs488/Winter2023/a5.html) final project.

The name "Kefka" comes from the main antagonist of my favorite game, [Final Fantasy VI](https://en.wikipedia.org/wiki/Final_Fantasy_VI). I've thought of this project as the "final boss" of my degree, so this name felt appropriate.

## Building and Running
Ensure the repo is cloned with submodules. A single `premake4` script is used to build the source and libraries:
```sh
$ premake4 gmake && make
```

Run the binary in the root directory (or else assets will fail to load):
```sh
$ ./fps
```

## UI
The main menu has two buttons: one that lets you start the game, and another that lets you tweak game parameters. The following can be changed from the options menu:
- World size
- Floor texture
- Wall texture
- Enemy texture
- Skybox

Pressing the `s` key at any time in the main menu will start the game with the currently selected parameters.

### Controls
The game is controlled using the mouse and keyboard. If you've played a first-person shooter on PC in the last 25 years, the controls should feel intuitive. In case you haven't:
- `w`: move forward
- `a`: move left
- `s`: move back
- `d`: move right
- `space`: jump
- `left shift`: hold to sprint
- `r`: respawn enemies
- `escape`: close game

The mouse is used to look around the world, and the left mouse button shoots.

## Libraries and Assets
Credit for all libraries and assets used in this repo go to their respective owners. The list of libraries and assets used are detailed in the following subsections.

### Libraries
- [gl3w](https://github.com/skaslev/gl3w)
  - The Unlicense

- [glfw](https://github.com/glfw/glfw)
  - zlib License

- [glm](https://github.com/g-truc/glm)
  - MIT License

- [ImGui](https://github.com/ocornut/imgui)
  - MIT License

- [stb](https://github.com/nothings/stb)
  - MIT License

- [SoLoud](https://github.com/jarikomppa/soloud)
  - zlib/libpng License

### Assets
- floor textures - https://opengameart.org/content/tileable-grass-textures-set-1
  - CC0 1.0

- wall textures - https://opengameart.org/content/wall-grass-rock-stone-wood-and-dirt-480
  - CC0 1.0

- fire textures - https://www.manytextures.com/texture/260/red+hot+fire+flames/
  - CC0 BY 4.0

- skybox textures - https://opengameart.org/content/stormy-days-skybox
  - CC BY 3.0

- skybox textures - https://opengameart.org/content/miramar-skybox
  - CC BY 3.0

- skybox textures - https://opengameart.org/content/space-skyboxes
  - CC0 1.0

- gun sound effect - https://opengameart.org/content/futuristic-shotgun
  - CC BY-SA 3.0

- footstep sound effects - https://opengameart.org/content/footsteps-on-different-surfaces
  - CC BY-SA 3.0

- jump sound effects - https://opengameart.org/content/15-vocal-male-strainhurtpainjump-sounds
  - CC BY-SA 3.0

- fonts - Roboto - https://fonts.google.com/specimen/Roboto
  - Apache-2.0

## Objectives
The project implements the first 8 objectives. The full list of objectives is as follows:

1. Model the scene for the player to move around in.
1. Main menu user interface that the player interacts with to start the game.
1. Texture mapping.
1. Particle system.
1. Synchronized sound corresponding to player actions.
1. Static collision detection of surrounding environment.
1. Dynamic collision detection of bullets fired by the player with enemies in the environment.
1. Physics engine with friction and gravity.
1. Shadows using shadow mapping (partially implemented, see the `shadow-mapping` branch).
1. Keyframe animation using linear interpolation (unimplemented).

