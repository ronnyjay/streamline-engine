# Streamline Engine

Cross-compatible, OpenGL based graphics engine written in modern C++.

## Getting Started

**1. Clone the repository:**

 Clone the repository with: `git clone git@github.com:ronnyjay/streamline-engine.git`

 After cloning, use: `git submodule update --init --recursive` to clone the necessary submodules.


**2. Install the necessary dependencies:**

- CMake
- GLFW
- OpenGL Mathematics (GLM)
- Assimp 

For ease of use, it is suggested to build all dependencies from source. 

Alternatively, macOS users can opt to install the necessary dependencies via Homebrew.

Note that at the time of installation, dependency versions may change and must be reflected in the top level CMake:

```cmake
set(GLM_OSX_INCLUDE_DIR "/opt/homebrew/Cellar/glm/1.0.1/include")
set(GLFW_OSX_INCLUDE_DIR "/opt/homebrew/Cellar/glfw/3.3.2/include")
set(ASSIMP_OSX_INCLUDE_DIR "/opt/homebrew/Cellar/assimp/5.4.1/include")
```

**3. Build:**

To build, simply use: `make run` in the root directory.

## Documentation
