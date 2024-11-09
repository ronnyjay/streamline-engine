#include "application.hpp"

using namespace engine;

Application::Application()
{
    mWindow = Window::create(800, 600, "Streamline Engine");

    mRenderer = new Renderer();
    mDisplayManager = new DisplayManager();

    mWindow->SetEventCallback(this, &Application::OnEvent);
}

void Application::Run()
{
    while (!glfwWindowShouldClose(*mWindow))
    {
        glfwPollEvents();

        if (glfwGetKey(*mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(*mWindow, GL_TRUE);
        }

        glfwSwapBuffers(*mWindow);
    }
}

void Application::OnEvent(Event &&e)
{
    EventDispatcher dispatcher(e);

    // Dispatch events here
}

Application::~Application()
{
    if (mWindow)
    {
        delete mWindow;
        mWindow = nullptr;
    }

    if (mRenderer)
    {
        delete mRenderer;
        mRenderer = nullptr;
    }

    if (mDisplayManager)
    {
        delete mDisplayManager;
        mDisplayManager = nullptr;
    }

    glfwTerminate();
}