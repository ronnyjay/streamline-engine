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

## Examples

Below is a brief example of creating a simple scene:

```C++
#include <engine/application/application.hpp>
#include <engine/camera/orthographic.hpp>
#include <engine/camera/perspective.hpp>
#include <engine/collider/collider.hpp>
#include <engine/components/components.hpp>
#include <engine/entity/entity.hpp>
#include <engine/model/model.hpp>

engine::Application application(800, 600, "Streamline Engine");

int main(int argc, char const *argv[])
{
    auto scene = std::make_shared<engine::Scene>();

    auto perspectiveCamera = std::make_shared<engine::PerspectiveCamera>();
    auto orthographicCamera = std::make_shared<engine::OrthographicCamera>();

    application.AddScene(0, scene);

    application.AddCamera(0, perspectiveCamera);
    application.AddCamera(1, orthographicCamera);
    application.SetCamera(0);

    application.BindMovementKey(GLFW_KEY_W, engine::Direction::Forward);
    application.BindMovementKey(GLFW_KEY_S, engine::Direction::Backward);
    application.BindMovementKey(GLFW_KEY_A, engine::Direction::Left);
    application.BindMovementKey(GLFW_KEY_D, engine::Direction::Right);
    application.BindMovementKey(GLFW_KEY_SPACE, engine::Direction::Up);
    application.BindMovementKey(GLFW_KEY_LEFT_SHIFT, engine::Direction::Down);

    auto cube = scene.get()->CreateEntity("Cube");
    auto torus = scene.get()->CreateEntity("Torus");
    auto pyramid = scene.get()->CreateEntity("Pyramid");

    cube.AddComponent<engine::Model>("resources/objects/cube/cube.obj");
    cube.AddComponent<engine::AABB>();
    cube.GetComponent<engine::Transform>().SetPosition(-10.0f, 5.0f, 0.0f);

    torus.AddComponent<engine::Model>("resources/objects/torus/torus.obj");
    torus.AddComponent<engine::AABB>();
    torus.GetComponent<engine::Transform>().SetPosition(0.0f, 0.0f, 0.0f);

    pyramid.AddComponent<engine::Model>("resources/objects/pyramid/pyramid.obj");
    pyramid.AddComponent<engine::AABB>();
    pyramid.GetComponent<engine::Transform>().SetPosition(10.0f, -5.0f, 0.0f);

    application.Run();

    return 0;
}
```
