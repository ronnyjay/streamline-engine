#include <engine/core/window.hpp>

using namespace engine;

int main(int argc, char const *argv[])
{
    engine::Window window(800, 600, "Window");

    window.on<WindowResizeEvent>(
        [](WindowResizeEvent &e)
        {
            return;
        });

    window.on<KeyPressedEvent>(
        [](KeyPressedEvent &e)
        {
            return;
        });

    window.on<MousePressedEvent>(
        [](MousePressedEvent &e)
        {
            return;
        });

    window.on<MouseMovedEvent>(
        [](MouseMovedEvent &e)
        {
            return;
        });

    window.on<MouseScrolledEvent>(
        [](MouseScrolledEvent &e)
        {
            return;
        });

    window.SetMonitor(0);

    window.SetDisplayMode(WINDOWED);

    window.SetResolution(Resolution(1920, 1080));

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
