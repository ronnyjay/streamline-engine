#include <engine/application/application.hpp>
#include <engine/stb/stb_image.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <stdexcept>

using namespace engine;

Application::Application(const int width, const int height, const char *title)
    : m_Width(width), m_Height(height), m_CurrentCamera(nullptr), m_CurrentScene(nullptr)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Initialize Window
    m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (m_Window == NULL)
    {
        throw std::runtime_error("Failed to create GLFW Window");
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowAspectRatio(m_Window, width, height);
    glfwSetFramebufferSizeCallback(m_Window, Application::FramebufferSizeCallback);
    glfwSetWindowIconifyCallback(m_Window, Application::MinimizeCallback);
    glfwSetWindowMaximizeCallback(m_Window, Application::MaximizeCallback);
    glfwSetKeyCallback(m_Window, Application::KeyCallback);
    glfwSetCursorPosCallback(m_Window, Application::CursorPosCallback);
    glfwSetScrollCallback(m_Window, Application::ScrollCallback);
    glfwSetWindowUserPointer(m_Window, this); // Access this objects instance in glfw callbacks

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to intialize GLAD");
    }

    m_Framebuffer.Initialize(width, height);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    // Setup Platform/Renderer backend
    // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init(nullptr);

    // Load shaders
    LoadShader("Model", "resources/shaders/model.vs", "resources/shaders/model.fs");
    LoadShader("Collider", "resources/shaders/collider.vs", "resources/shaders/collider.fs");
    LoadShader("Framebuffer", "resources/shaders/framebuffer.vs", "resources/shaders/framebuffer.fs");

    // Flip textures on load
    stbi_set_flip_vertically_on_load(true);
}

int Application::Width() const
{
    return m_Width;
}

int Application::Height() const
{
    return m_Height;
}

ApplicationFlags const &Application::Flags() const
{
    return m_Flags;
}

void Application::AddCamera(int key, std::shared_ptr<Camera> camera)
{
    m_CameraMap[key] = camera;

    if (m_CurrentCamera == nullptr)
    {
        m_CurrentCamera = camera.get();
        m_CurrentCameraIndex = key;
    }
}

void Application::SetCamera(int key)
{
    auto it = m_CameraMap.find(key);

    if (it == m_CameraMap.end())
    {
        throw std::out_of_range("Camera not found");
    }

    m_CurrentCamera = it->second.get();
    m_CurrentCameraIndex = it->first;
}

Camera *const Application::GetCurrentCamera() const
{
    return m_CurrentCamera;
}

void Application::AddScene(int key, std::shared_ptr<Scene> scene)
{
    m_SceneMap[key] = scene;

    if (m_CurrentScene == nullptr)
    {
        m_CurrentScene = scene.get();
        m_CurrentSceneIndex = key;
    }
}

void Application::SetScene(int key)
{
    auto it = m_SceneMap.find(key);

    if (it == m_SceneMap.end())
    {
        throw std::out_of_range("Scene not found");
    }

    m_CurrentScene = it->second.get();
    m_CurrentSceneIndex = it->first;
}

Scene *const Application::GetCurrentScene() const
{
    return m_CurrentScene;
}

void Application::LoadShader(const std::string &shader, const std::string &vertexPath, const std::string &fragmentPath)
{
    m_ShaderMap.emplace(shader, Shader(vertexPath, fragmentPath));
}

Shader &Application::GetShader(const std::string &shader)
{
    auto it = m_ShaderMap.find(shader);

    if (it == m_ShaderMap.end())
    {
        throw std::runtime_error("Shader not found");
    }

    return it->second;
}

void Application::ShowWireframes(const bool value)
{
    m_Flags.ShowWireframes = value;

    ToggleWireframes();
}

void Application::ShowCollisions(const bool value)
{
    m_Flags.ShowCollisions = value;
}

void Application::BindMovementKey(const int key, const Direction direction)
{
    m_KeyMap[key] = direction;
}

void Application::Run()
{
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    double currentTime;
    double lastTime;
    double deltaTime;

    lastTime = currentTime = glfwGetTime();

    while (!glfwWindowShouldClose(m_Window))
    {
        deltaTime = (currentTime = glfwGetTime()) - lastTime;

        auto monitor = GetMonitor();

        if (monitor && monitor != m_Monitor)
        {
            m_Monitor = monitor;

            LoadResolutions();
        }

        ProcessInput();

        // Render scene
        m_Framebuffer.Bind();

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, m_Framebuffer.Width(), m_Framebuffer.Height());

        m_CurrentScene->Update(deltaTime);
        m_CurrentScene->Draw();

        m_Framebuffer.Unbind();

        glDisable(GL_DEPTH_TEST);
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        int width, height;
        glfwGetFramebufferSize(m_Window, &width, &height);
        glViewport(0, 0, width, height);

        m_Framebuffer.Draw();

        // Draw Debug Info
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (m_Flags.ShowDebugWindow)
        {
            if (ImGui::Begin("Streamline Engine Debugger", &m_Flags.ShowDebugWindow))
            {
                if (ImGui::Button("Show Metrics"))
                {
                    m_Flags.ShowMetrics = !m_Flags.ShowMetrics;
                }

                if (m_Flags.ShowMetrics)
                {
                    ImGui::ShowMetricsWindow();
                }

                if (ImGui::TreeNode("Settings"))
                {
                    ImGui::Text("Show Wireframes");
                    ImGui::SameLine();

                    if (ImGui::Checkbox("##Wireframes", &m_Flags.ShowWireframes))
                    {
                        ToggleWireframes();
                    }

                    ImGui::Text("Show Collisions");
                    ImGui::SameLine();
                    ImGui::Checkbox("##Collisions", &m_Flags.ShowCollisions);

                    ImGui::Text("Set Resolution");
                    ImGui::SameLine();

                    if (ImGui::Combo(
                            "##Resolution", &m_ResolutionIndex,
                            [](void *data, int index, const char **text) -> bool
                            {
                                auto &vector = *static_cast<std::vector<Resolution> *>(data);

                                if (index < 0 || index >= static_cast<int>(vector.size()))
                                {
                                    return false;
                                }
                                *text = vector[index].Format();

                                return true;
                            },
                            static_cast<void *>(&m_ResolutionList), m_ResolutionList.size()))
                    {
                        auto resolution = m_ResolutionList[m_ResolutionIndex];

                        if (!IsFullscreen())
                        {
                            float scaleX = 1.0f;
                            float scaleY = 1.0f;

                            if (auto monitor = GetMonitor())
                            {
                                glfwGetMonitorContentScale(monitor, &scaleX, &scaleY);
                            }

                            glfwSetWindowAspectRatio(m_Window, GLFW_DONT_CARE, GLFW_DONT_CARE);
                            glfwSetWindowSize(m_Window, resolution.Width / scaleX, resolution.Height / scaleY);
                            glfwSetWindowAspectRatio(m_Window, resolution.Width, resolution.Height);
                        }

                        m_Framebuffer.Resize(resolution.Width, resolution.Height);
                    }

                    ImGui::Text("Current Resolution: %dx%d", m_Framebuffer.Width(), m_Framebuffer.Height());

                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("Camera"))
                {
                    if (m_CameraMap.size())
                    {
                        ImGui::Text("Current:");
                        ImGui::SameLine();

                        if (ImGui::ArrowButton("Camera Previous", ImGuiDir_Left))
                        {
                            SetCameraPrev();
                        }

                        ImGui::SameLine();
                        ImGui::TextUnformatted(std::to_string(m_CurrentCameraIndex).c_str());
                        ImGui::SameLine();

                        if (ImGui::ArrowButton("Camera Next", ImGuiDir_Right))
                        {
                            SetCameraNext();
                        }

                        m_CurrentCamera->DrawDebugInfo();
                    }
                    else
                    {
                        ImGui::Text("Camera information unavailable");
                    }

                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("Scene"))
                {
                    if (m_SceneMap.size())
                    {
                        ImGui::Text("Current:");
                        ImGui::SameLine();

                        if (ImGui::ArrowButton("Scene Previous", ImGuiDir_Left))
                        {
                            SetScenePrev();
                        }

                        ImGui::SameLine();
                        ImGui::TextUnformatted(std::to_string(m_CurrentSceneIndex).c_str());
                        ImGui::SameLine();

                        if (ImGui::ArrowButton("Scene Next", ImGuiDir_Right))
                        {
                            SetSceneNext();
                        }

                        m_CurrentScene->DrawDebugInfo();
                    }
                    else
                    {
                        ImGui::Text("Scene information unavailable");
                    }

                    ImGui::TreePop();
                }

                ImGui::End();
            }
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window);
        glfwPollEvents();

        lastTime = currentTime;
    }
}

GLFWwindow *const Application::GetWindow() const
{
    return m_Window;
}

GLFWmonitor *const Application::GetMonitor() const
{
    GLFWmonitor *monitor = glfwGetWindowMonitor(m_Window);

    if (monitor)
    {
        return monitor;
    }

    int windowX, windowY;
    glfwGetWindowPos(m_Window, &windowX, &windowY);

    int monitorCount;
    GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);

    for (int i = 0; i < monitorCount; i++)
    {
        int monitorX, monitorY;
        int monitorWidth, monitorHeight;
        glfwGetMonitorWorkarea(monitors[i], &monitorX, &monitorY, &monitorWidth, &monitorHeight);

        bool overlapX = windowX >= monitorX && windowX < monitorX + monitorWidth;
        bool overlapY = windowY >= monitorY && windowY < monitorY + monitorHeight;

        if (overlapX && overlapY)
        {
            return monitors[i];
        }
    }

    return nullptr;
}

bool Application::IsFullscreen()
{
    Resolution fullscreen = m_ResolutionList[m_ResolutionList.size() - 1];

    int width, height;
    glfwGetWindowSize(m_Window, &width, &height);

    if (width == fullscreen.Width && height == fullscreen.Height)
    {
        return true;
    }

    return false;
}

void Application::LoadResolutions()
{
    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(m_Monitor, &count);

    m_ResolutionList.clear();

    for (int i = 0; i < count; i++)
    {
        m_ResolutionList.emplace_back(Resolution(modes[i].width, modes[i].height));
    }

    m_ResolutionList.erase(std::unique(m_ResolutionList.begin(), m_ResolutionList.end()), m_ResolutionList.end());
}

void Application::ProcessInput()
{
    for (auto it = m_KeyMap.begin(); it != m_KeyMap.end(); ++it)
    {
        if (glfwGetKey(m_Window, it->first) == GLFW_PRESS)
        {
            m_CurrentCamera->Move(Direction(it->second));
        }

        if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_Window, true);
        }
    }
}

void Application::SetCameraNext()
{
    auto it = m_CameraMap.find(m_CurrentCameraIndex);

    if ((it = std::next(it)) == m_CameraMap.end())
    {
        it = m_CameraMap.begin();
    }

    m_CurrentCamera = it->second.get();
    m_CurrentCameraIndex = it->first;
}

void Application::SetCameraPrev()
{
    auto it = m_CameraMap.find(m_CurrentCameraIndex);

    if (it == m_CameraMap.begin())
    {
        it = std::prev(m_CameraMap.end());
    }
    else
    {
        it = std::prev(it);
    }

    m_CurrentCamera = it->second.get();
    m_CurrentCameraIndex = it->first;
}

void Application::SetSceneNext()
{
    auto it = m_SceneMap.find(m_CurrentSceneIndex);

    if ((it = std::next(it)) == m_SceneMap.end())
    {
        it = m_SceneMap.begin();
    }

    m_CurrentScene = it->second.get();
    m_CurrentSceneIndex = it->first;
}

void Application::SetScenePrev()
{
    auto it = m_SceneMap.find(m_CurrentSceneIndex);

    if (it == m_SceneMap.begin())
    {
        it = std::prev(m_SceneMap.end());
    }
    else
    {
        it = std::prev(it);
    }

    m_CurrentScene = it->second.get();
    m_CurrentSceneIndex = it->first;
}

void Application::ToggleWireframes()
{
    if (m_Flags.ShowWireframes)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

Application::~Application()
{
    glfwTerminate();
}

void Application::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));

    application->m_Width = width;
    application->m_Height = height;
}

void Application::MinimizeCallback(GLFWwindow *window, int minimize)
{
    (minimize) ? glfwIconifyWindow(window) : glfwRestoreWindow(window);
}

void Application::MaximizeCallback(GLFWwindow *window, int maximize)
{
    (maximize) ? glfwMaximizeWindow(window) : glfwRestoreWindow(window);
}

void Application::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
    {
        if (mods == GLFW_MOD_SHIFT)
        {
            application->m_Flags.ShowCursor = !application->m_Flags.ShowCursor;

            if (application->m_Flags.ShowCursor)
            {
                glfwSetInputMode(application->m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(application->m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }

            application->m_Flags.FirstMouse = true;
        }
        else
        {
            application->m_Flags.ShowDebugWindow = !application->m_Flags.ShowDebugWindow;

            if (application->m_Flags.ShowDebugWindow)
            {
                application->m_Flags.CaptureMouse = false;

                // Temporarily show cursor while debug window is open
                if (!application->m_Flags.ShowCursor)
                {
                    glfwSetInputMode(application->m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }

                application->m_Flags.FirstMouse = true;
            }
            else
            {
                application->m_Flags.CaptureMouse = true;

                // Restore cursor state
                if (!application->m_Flags.ShowCursor)
                {
                    glfwSetInputMode(application->m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
            }
        }
    }
}

void Application::CursorPosCallback(GLFWwindow *window, double xPosIn, double yPosIn)
{
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));

    static float lastX = application->Width() / 2.0f;
    static float lastY = application->Height() / 2.0f;

    if (!application->m_Flags.CaptureMouse)
    {
        return;
    }

    if (application->m_Flags.FirstMouse)
    {
        lastX = xPosIn;
        lastY = yPosIn;
        application->m_Flags.FirstMouse = false;
    }

    float xPos = static_cast<float>(xPosIn);
    float yPos = static_cast<float>(yPosIn);

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    application->m_CurrentCamera->Move(xOffset, yOffset);
}

void Application::ScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
    Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));

    if (application->m_Flags.ShowDebugWindow)
    {
        return;
    }

    application->m_CurrentCamera->Move(yOffset);
}