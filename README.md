# CS488 Project
A first-person shooter game engine written for the [CS488](https://student.cs.uwaterloo.ca/~cs488/Winter2023/a5.html) final project.

The name "Kefka" comes from the main antagonist of my favorite game, [Final Fantasy VI](https://en.wikipedia.org/wiki/Final_Fantasy_VI). I've thought of this project as the "final boss" of my degree, so this name felt appropriate.

## Building and Running
A single `premake4` script is used to build the source and libraries:
```sh
$ premake4 gmake && make
```

Run the binary in the root directory (or else assets will fail to load):
```sh
$ ./fps
```

## Controls
The game is controlled using the mouse and keyboard. If you've played a first-person shooter on PC in the last 25 years, the controls should feel intuitive. In case you haven't:
- `w`: move foward
- `a`: move left
- `s`: move back
- `d`: move right
- `space`: jump
- `left shift`: hold to sprint
- `r`: respawn enemies

The mouse is used to look around the world, and the left mouse button shoots.

## Libraries and Assets
Credit for all libraries and assets used in this repo go to their respective owners. The list of libraries and assets used are detailed in the following subsections.

### Libraries
- gl3w - https://github.com/skaslev/gl3w
  - The Unlicense

- glfw - https://github.com/glfw/glfw
  - zlib License

- glm - https://github.com/g-truc/glm
  - MIT License

- ImGui - https://github.com/ocornut/imgui
  - MIT License

- stb (image loader) - https://github.com/nothings/stb/blob/master/stb_image.h
  - MIT License

- SoLoud - https://github.com/jarikomppa/soloud
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

