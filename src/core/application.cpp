#include <core/application.hpp>

using namespace engine;

Application::Application()
{
    mWindow = Window::Create(800, 600, "Streamline Engine");

    mDisplayManager = std::make_unique<DisplayManager>();

    DisplayManager::GetInstancePtr()->Init();
    DisplayManager::GetInstancePtr()->AttachWindow(mWindow);

    mWindow->SetEventCallback(this, &Application::OnEvent);
}

void Application::Run()
{
    while (mWindow->IsOpen())
    {
        glfwPollEvents();

        if (glfwGetKey(*mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            mWindow->Close();
        }

        mWindow->SwapBuffers();
    }
}

void Application::OnEvent(Event &&e)
{
    EventDispatcher dispatcher(e);

    // handle resize from within application
    dispatcher.Dispatch<WindowResizeEvent>(this, &Application::OnWindowResize);

    // dispatch events to various singletons
    DisplayManager::GetInstancePtr()->OnEvent(e);
}

bool Application::OnWindowResize(WindowResizeEvent &e)
{
    // mRenderer->OnViewportResize(e.width, e.height);

    return true;
}

Application::~Application()
{

    if (mWindow)
    {
        delete mWindow;
        mWindow = nullptr;
    }
}