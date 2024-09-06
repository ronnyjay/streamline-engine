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

    window.set_monitor(0);

    window.set_resolution(800, 600);

    window.set_display_mode(engine::WINDOWED);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
