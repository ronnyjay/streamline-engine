#include "core/application.hpp"

#include <cstdio>

using namespace engine;

Application::Application()
    : mWindow(800, 600, "Streamline Engine")
{
    mWindow.on<WindowResizeEvent>(
        [this](WindowResizeEvent &e) {

        });

    mWindow.on<KeyPressEvent>(
        [this](KeyPressEvent &e) {

        });

    mWindow.on<KeyReleaseEvent>(
        [this](KeyReleaseEvent &e) {

        });

    mWindow.on<MouseMoveEvent>(
        [this](MouseMoveEvent &e) {

        });

    mWindow.on<MouseScrollEvent>(
        [this](MouseScrollEvent &e) {

        });

    mWindow.on<MouseButtonPressEvent>(
        [this](MouseButtonPressEvent &e) {

        });

    mWindow.on<MouseButtonReleaseEvent>(
        [this](MouseButtonReleaseEvent &e) {

        });
}

void Application::run()
{
    while (mWindow.IsRunning())
    {
        mWindow.SwapBuffers();
    }
}