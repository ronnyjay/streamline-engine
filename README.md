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

## Documentation

### Application

The application is responsible for managing the OpenGL context and overseeing various functionalities within the engine.

#### Initial Setup and Configuration

Upon launch, the application attempts to load the video configuration stored from previous sessions. If no configuration is found, such as on first launch, the application will result to predefined settings:

**Title**: Initialized with a default title of "Untitled Application" unless specified otherwise.

**Resolution**: Initialized with a resolution of 800x600 pixels unless specified otherwise.

**Monitor**: Defaults to the primary monitor as specified by the operating system. 

-   ***Note***: Despite the application defaulting to the operating system's primary monitor, the engine will initially launch on the monitor in which the application was initialized.


**Display Mode**: Windowed.

**Vertical Sync**: Disabled.

**Frame Rate Limit**: Unlimited.

#### Monitors

By default, the application will utilize the operating system's primary monitor. If a different monitor is desired, this preference can be changed in the application's video settings menu. It is important to note that this option is disabled when the application is running in the windowed display mode. 

When switching monitors in either the fullscreen or fullscreen windowed display modes, the application will maintain the specified display mode on the new monitor.

#### Resolutions

Resolutions will be listed based on the supported resolutions of the monitor within which the application is displayed, not the specified monitor. This approach ensures that resolutions always scale appropriately according to the type of display, particularly as HiDPI displays often utilize different scaling factors. Additionally, it guarantees that the list of available resolutions is always contextually accurate.

#### Display Modes

**Fullscreen**: In this mode, the application occupies the entire display. Upon switching to fullscreen, the application will use the monitor specified in the video configuration or the monitor currently set by the user in the application's video settings. The application will then query the selected monitor's video mode using `glfwGetVideoMode(monitor)`, which typically returns the highest supported resolution and refresh rate. However, in some cases, a lower resolution may be returned.

**Windowed**: In this mode, the application runs in a standard window with window decorations enabled. The size of the window can be changed in the video settings menu. Changes to the specified monitor are disabled in this mode as it has no effect. Instead, the window can be moved freely around the desktop, refreshing the list of supported resolutions based on the monitor within which the window is currently displayed.

**Fullscreen Windowed**: In this mode, the application operates in a borderless window that spans the work area of the monitor specified in the video configuration or the monitor currently set by the user in the application's video settings, with window decorations disabled. Upon switching to fullscreen windowed, the application will retrieve the monitor's work area dimensions using `glfwGetMonitorWorkArea(monitor)` and adjusts the windows position and size accordingly. Changes to resolution are disabled in this mode.
