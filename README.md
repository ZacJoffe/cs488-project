# CS488 Project

## Building and Running
A single `premake4` script is used to build the source and libraries:
```sh
$ premake4 gmake && make
```

Run the binary in the root directory (or else assets will fail to load):
```sh
$ ./fps
```


### Libs
- stb image loader - https://github.com/nothings/stb/blob/master/stb_image.h
  - MIT

- SoLoud - https://github.com/jarikomppa/soloud
  - zlib/libpng

### Assets
- textures - https://opengameart.org/content/tileable-grass-textures-set-1
  - CC0 1.0 Universal

- textures - https://opengameart.org/content/wall-grass-rock-stone-wood-and-dirt-480
  - CC0 1.0 Universal

- gun - https://opengameart.org/content/high-poly-ak-47
  - CC0 1.0 Universal

- textures - https://www.manytextures.com/texture/260/red+hot+fire+flames/
  - CC0 BY 4.0

- gun sound effect - https://opengameart.org/content/futuristic-shotgun
  - CC BY-SA 3.0
