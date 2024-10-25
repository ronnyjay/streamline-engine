#include "core/application.hpp"

#include <cstdio>

using namespace engine;

Application::Application()
    : m_window(800, 600, "Streamline Engine")
{
    m_window.on<WindowResizeEvent>(
        [this](WindowResizeEvent &e) {

        });

    m_window.on<KeyPressEvent>(
        [this](KeyPressEvent &e) {

        });

    m_window.on<KeyReleaseEvent>(
        [this](KeyReleaseEvent &e) {

        });

    m_window.on<MouseMoveEvent>(
        [this](MouseMoveEvent &e) {

        });

    m_window.on<MouseScrollEvent>(
        [this](MouseScrollEvent &e) {

        });

    m_window.on<MouseButtonPressEvent>(
        [this](MouseButtonPressEvent &e) {

        });

    m_window.on<MouseButtonReleaseEvent>(
        [this](MouseButtonReleaseEvent &e) {

        });
}

void Application::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}