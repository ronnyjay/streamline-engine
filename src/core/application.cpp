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
    while (mWindow->IsOpen())
    {
        glfwPollEvents();

        if (glfwGetKey(*mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            mWindow->RequestClose();
        }

        mWindow->SwapBuffers();
    }
}

void Application::OnEvent(Event &&e)
{
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<WindowResizeEvent>(this, &Application::OnWindowResize);
}

bool Application::OnWindowResize(WindowResizeEvent &e)
{
    mRenderer->OnViewportResize(e.width, e.height);

    return true;
}

Application::~Application()
{
    if (mDisplayManager)
    {
        delete mDisplayManager;
        mDisplayManager = nullptr;
    }

    if (mRenderer)
    {
        delete mRenderer;
        mRenderer = nullptr;
    }

    if (mWindow)
    {
        delete mWindow;
        mWindow = nullptr;
    }
}