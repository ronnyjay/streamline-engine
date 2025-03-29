# Streamline Engine

Cross-compatible, OpenGL based graphics engine written in C++.

## Getting Started

**1. Clone the repository**

Clone the respository with: `git clone https://github.com/ronnyjay/streamline-engine.git`

After cloning, use: `git submodule update --init --recursive` to clone the necessary submodules.

**2. Install the necessary dependencies**

- CMake
- GLFW
- Assimp
- OpenGL Mathematics (GLM)

**Linux**

Use your distributions package manager to install the necessary dependencies. The examples list below use [pacman](https://wiki.archlinux.org/title/Pacman) as Streamline Engine is primarly developed on Arch Linux:

- `sudo pacman -S glfw`
- `sudo pacman -S assimp`
- `sudo pacman -S glm`

**Windows**

For windows users, it is recommended to use [MSYS2](https://www.msys2.org/) to install the necessary dependencies. Instructions for installation and setup can be found at the link above. Additonally, the following guide can be used as a reference for integrating MSYS2 with Visual Studio Code: [Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw).

The following commands have been provided for your convenience (it can be somewhat of tedious to find the correct packages):

- `pacman -S mingw-w64-ucrt-x86_64-glfw`
- `pacman -S mingw-w64-ucrt-x86_64-assimp`
- `pacman -S mingw-w64-ucrt-x86_64-glm`

**MacOS**

MacOS users can use homebrew to install the necessary dependencies:

- `brew install glfw`
- `brew install assimp`
- `brew install glm`

*Note: Streamline Engine is primarily developed on Arch Linux. Although the engine will (hopefully) compile on all platforms, testing may be inconsistent and some breakages are to be expected until completion. If possible, it is recommended to use a **linux distribution** for ease of use.*

## To-Do 

A (somewhat) comprehensive lists of changes/features that should be implemented, in no particular order:

- Decouple rendering from scene logic 
- Scene heirarchy
    - Implement parent/child relationships between entities 
- Lighting system
    - Implement point/directional lighting system
    - Implement depth buffer for shadow mapping
- Physics System
    - Implement rigid body dynamics
    - Implement bounding volumes (AABB, OBB, BSphere)
    - Implement collision detection/resolution 
- Seperate player control and camera control logic
    - PlayerController component currently controls camera movement. This should be removed in favor of a seperate camera controller for more complex behaviours such as vehicle control. 