# SDL2 Framework
A basic SDL2 framework meant for games. Mostly created as practice for learning C++. There's most likely a lot of mistakes.

Current feature list:
* Texture rendering (basic wrapper over SDL2_Image)
* Sprite rendering (render sprites from a sprite sheet. Built ontop of the Texture class)
* Tilemap rendering (renders tilemaps from the software Tiled)


# Building
There is no official support from me on how to build this project beyond basic instructions (mostly because it's a mess and I'm not adept with build systems like this yet) 

Building this project requires:
* [CMake](https://cmake.org/)
* [MinGW](https://www.mingw-w64.org/) (project is setup to use MinGW makefiles)
* [TMXLite](https://github.com/fallahn/tmxlite)
* [SDL2](https://github.com/libsdl-org/SDL)

My cmake cache(?) looks like this:
![image](https://github.com/BradFitz66/SDL2-Framework/assets/28825575/93d8350c-4aef-4e2c-a932-2b8ac6e5b970)


The code, as it is, is setup to render a basic tilemap which is not included with this repository.
[You should remove or replace any references to 'tilemap' inside main.cpp in order to build this](https://github.com/BradFitz66/SDL2-Framework/blob/main/src/main.cpp#L66)



# Licensing stuff
This project uses imgui (unmodified) for debug and UI purposes and includes it inside thirdparty/imgui
