#include <engine/application/application.hpp>
#include <engine/stb/stb_image.hpp>
#include <engine/text/text.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <stdexcept>

using namespace engine;

// clang-format off
const char *Application::DisplayModes[] = {
    "Fullscreen",
    "Windowed",
    "Windowed Borderless"
};

const char *Application::Framerates[] = {
    "30 FPS",
    "60 FPS",
    "120 FPS",
    "144 FPS",
    "165 FPS",
    "240 FPS",
    "360 FPS",
    "Unlimited"
};
// clang-format on

Application::Application(const int width, const int height, const char *title)
    : m_Width(width), m_Height(height), m_FramerateIndex(7), m_Framerate(FPS_UNLIMITED), m_DisplayMode(Windowed),
      m_CurrentCamera(nullptr), m_CurrentScene(nullptr)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

    // Initialize framebuffer
    m_Framebuffer = new Framebuffer(width, height);

    if (!m_Framebuffer)
    {
        throw std::runtime_error("Error creating framebuffer");
    }

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

    if (!m_Flags.ShowCursor)
    {
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

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

void Application::AddCamera(const int key, const std::shared_ptr<Camera> camera)
{
    m_Cameras[key] = camera;

    if (m_CurrentCamera == nullptr)
    {
        m_CurrentCamera = camera.get();
        m_CurrentCameraIndex = key;
    }
}

void Application::SetCamera(int key)
{
    auto it = m_Cameras.find(key);

    if (it == m_Cameras.end())
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

void Application::AddScene(const int key, const std::shared_ptr<Scene> scene)
{
    m_Scenes[key] = scene;

    if (m_CurrentScene == nullptr)
    {
        m_CurrentScene = scene.get();
        m_CurrentSceneIndex = key;
    }
}

void Application::SetScene(int key)
{
    auto it = m_Scenes.find(key);

    if (it == m_Scenes.end())
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

Shader Application::LoadShader(const char *name, const char *vertexPath, const char *fragmentPath)
{
    Shader shader = Shader::FromFile(vertexPath, fragmentPath);

    m_Shaders[name] = shader;

    return shader;
}

Shader Application::GetShader(const char *name)
{
    auto it = m_Shaders.find(name);

    if (it == m_Shaders.end())
    {
        throw std::runtime_error("Shader not found");
    }

    return it->second;
}

Texture Application::LoadTexture(const char *name, const char *path)
{
    Texture texture = Texture::FromFile(path);

    m_Textures[name] = texture;

    return texture;
}

Texture Application::GetTexture(const char *name)
{
    auto it = m_Textures.find(name);

    if (it == m_Textures.end())
    {
        throw std::runtime_error("Texture not found");
    }

    return it->second;
}

void Application::BindMovementKey(const int key, const Direction direction)
{
    m_MovementBinds[key] = direction;
}

void Application::ShowWireframes(const bool value)
{
    m_Flags.ShowWireframes = value;
}

void Application::ShowCollisions(const bool value)
{
    m_Flags.ShowCollisions = value;
}

void Application::Run()
{
    glfwSwapInterval(m_Flags.VerticalSync);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthFunc(GL_LESS);

    double currentTime;
    double lastTime;
    double deltaTime;

    double renderTimeStep;
    double renderAccumulator = 0.0;

    double simulationTimeStep = 1.0 / 300.0;
    double simulationAccumulator = 0.0;

    lastTime = currentTime = glfwGetTime();

    while (!glfwWindowShouldClose(m_Window))
    {
        deltaTime = (currentTime = glfwGetTime()) - lastTime;

        if (m_Framerate == FPS_UNLIMITED)
        {
            renderTimeStep = deltaTime;
        }
        else
        {
            renderTimeStep = 1.0 / static_cast<double>(m_Framerate);
        }

        renderAccumulator += deltaTime;
        simulationAccumulator += deltaTime;

        auto monitor = GetMonitor();

        if (monitor && monitor != m_Monitor)
        {
            m_Monitor = monitor;

            LoadResolutions();
        }

        ProcessInput(deltaTime);

        while (simulationAccumulator >= simulationTimeStep)
        {
            m_CurrentScene->Update(simulationTimeStep);

            simulationAccumulator -= simulationTimeStep;
        }

        if (renderAccumulator >= renderTimeStep)
        {
            // Begin rendering to framebuffer
            m_Framebuffer->Bind();

            glEnable(GL_DEPTH_TEST);
            glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, m_Framebuffer->Width(), m_Framebuffer->Height());

            if (m_Flags.ShowWireframes)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }

            // Draw scene
            m_CurrentScene->Draw();

            // End rendering to framebuffer
            m_Framebuffer->Unbind();

            int width, height;
            glfwGetFramebufferSize(m_Window, &width, &height);

            glDisable(GL_DEPTH_TEST);
            glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glViewport(0, 0, width, height);

            if (m_Flags.ShowWireframes)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            // Render framebuffer texture
            m_Framebuffer->Render();

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

                    if (ImGui::TreeNode("Debug"))
                    {
                        ImGui::Checkbox("Show Wireframes", &m_Flags.ShowWireframes);
                        ImGui::Checkbox("Show Collisions", &m_Flags.ShowCollisions);

                        ImGui::TreePop();
                    }

                    if (ImGui::TreeNode("Video"))
                    {
                        // Lock resolution if windowed borderless
                        if (m_DisplayMode == Borderless)
                        {
                            ImGui::BeginDisabled(true);
                        }

                        if (ImGui::Combo(
                                "Resolution", &m_ResolutionIndex,
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
                                static_cast<void *>(&m_Resolutions), m_Resolutions.size()))
                        {
                            SetResolution(m_Resolutions[m_ResolutionIndex]);
                        }

                        if (m_DisplayMode == Borderless)
                        {
                            ImGui::EndDisabled();
                        }

                        if (ImGui::Combo("Display Mode", (int *)&m_DisplayMode, DisplayModes, IM_ARRAYSIZE(DisplayModes)))
                        {
                            SetDisplayMode(m_DisplayMode);
                        }

                        if (ImGui::Combo("Frame Rate Limit", &m_FramerateIndex, Framerates, IM_ARRAYSIZE(Framerates)))
                        {
                            switch (m_FramerateIndex)
                            {
                            case 0:
                                m_Framerate = FPS_30;
                                break;
                            case 1:
                                m_Framerate = FPS_60;
                                break;
                            case 2:
                                m_Framerate = FPS_120;
                                break;
                            case 3:
                                m_Framerate = FPS_144;
                                break;
                            case 4:
                                m_Framerate = FPS_165;
                                break;
                            case 5:
                                m_Framerate = FPS_240;
                                break;
                            case 6:
                                m_Framerate = FPS_360;
                                break;
                            case 7:
                                m_Framerate = FPS_UNLIMITED;
                                break;
                            default:
                                break;
                            }
                        }

                        if (ImGui::Checkbox("Vertical Sync", &m_Flags.VerticalSync))
                        {
                            glfwSwapInterval(m_Flags.VerticalSync);
                        }

                        ImGui::TreePop();
                    }

                    if (ImGui::TreeNode("Camera"))
                    {
                        if (m_Cameras.size())
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
                        if (m_Scenes.size())
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

            renderAccumulator = 0.0;
        }

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

void Application::ProcessInput(const double timeStep)
{
    for (auto it = m_MovementBinds.begin(); it != m_MovementBinds.end(); ++it)
    {
        if (glfwGetKey(m_Window, it->first) == GLFW_PRESS)
        {
            m_CurrentCamera->Move(Direction(it->second), timeStep);
        }

        if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_Window, true);
        }
    }
}

void Application::SetCameraNext()
{
    auto it = m_Cameras.find(m_CurrentCameraIndex);

    if ((it = std::next(it)) == m_Cameras.end())
    {
        it = m_Cameras.begin();
    }

    m_CurrentCamera = it->second.get();
    m_CurrentCameraIndex = it->first;
}

void Application::SetCameraPrev()
{
    auto it = m_Cameras.find(m_CurrentCameraIndex);

    if (it == m_Cameras.begin())
    {
        it = std::prev(m_Cameras.end());
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
    auto it = m_Scenes.find(m_CurrentSceneIndex);

    if ((it = std::next(it)) == m_Scenes.end())
    {
        it = m_Scenes.begin();
    }

    m_CurrentScene = it->second.get();
    m_CurrentSceneIndex = it->first;
}

void Application::SetScenePrev()
{
    auto it = m_Scenes.find(m_CurrentSceneIndex);

    if (it == m_Scenes.begin())
    {
        it = std::prev(m_Scenes.end());
    }
    else
    {
        it = std::prev(it);
    }

    m_CurrentScene = it->second.get();
    m_CurrentSceneIndex = it->first;
}

void Application::SetResolution(const Resolution resolution)
{
    // Get scale for HiDPI displays
    float scaleX = 1.0f;
    float scaleY = 1.0f;

    if (auto monitor = GetMonitor())
    {
        glfwGetMonitorContentScale(monitor, &scaleX, &scaleY);
    }

    // Set resolution
    glfwSetWindowAspectRatio(m_Window, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowSize(m_Window, resolution.Width / scaleX, resolution.Height / scaleY);
    glfwSetWindowAspectRatio(m_Window, resolution.Width, resolution.Height);

    m_Framebuffer->Resize(resolution.Width, resolution.Height);
}

void Application::SetDisplayMode(const DisplayMode mode)
{
    if (mode == Borderless)
    {
        glfwSetWindowAttrib(m_Window, GLFW_DECORATED, GL_FALSE);
        glfwSetWindowAttrib(m_Window, GLFW_FLOATING, GL_TRUE);

        int monitorX, monitorY;
        int monitorWidth, monitorHeight;
        glfwGetMonitorWorkarea(m_Monitor, &monitorX, &monitorY, &monitorWidth, &monitorHeight);

        glfwGetWindowPos(m_Window, &m_WindowX, &m_WindowY);
        glfwGetWindowSize(m_Window, &m_LastWidth, &m_LastHeight);
        glfwSetWindowMonitor(m_Window, nullptr, monitorX, monitorY, monitorWidth, monitorHeight, 0);

        m_Framebuffer->Resize(monitorWidth, monitorHeight);

        m_LastResolutionIndex = m_ResolutionIndex;

        // Resolution will always be highest supported
        m_ResolutionIndex = m_Resolutions.size() - 1;
    }
    else
    {
        glfwSetWindowAttrib(m_Window, GLFW_DECORATED, GL_TRUE);
        glfwSetWindowAttrib(m_Window, GLFW_FLOATING, GL_FALSE);

        if (mode == Fullscreen)
        {
            const GLFWvidmode *mode = glfwGetVideoMode(m_Monitor);

            glfwGetWindowPos(m_Window, &m_WindowX, &m_WindowY);
            glfwGetWindowSize(m_Window, &m_LastWidth, &m_LastHeight);
            glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

            m_Framebuffer->Resize(mode->width, mode->height);

            m_LastResolutionIndex = m_ResolutionIndex;

            for (int i = 0; i < m_Resolutions.size(); i++)
            {
                auto resolution = m_Resolutions[i];

                if (resolution.Width == mode->width && resolution.Height == mode->height)
                {
                    m_ResolutionIndex = i;
                }
            }
        }
        else
        {
            glfwSetWindowMonitor(m_Window, nullptr, m_WindowX, m_WindowY, m_LastWidth, m_LastHeight, 0);

            m_Framebuffer->Resize(m_LastWidth, m_LastHeight);

            m_ResolutionIndex = m_LastResolutionIndex;
        }
    }
}

void Application::LoadResolutions()
{
    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(m_Monitor, &count);

    m_Resolutions.clear();

    for (int i = 0; i < count; i++)
    {
        m_Resolutions.emplace_back(Resolution(modes[i].width, modes[i].height));
    }

    m_Resolutions.erase(std::unique(m_Resolutions.begin(), m_Resolutions.end()), m_Resolutions.end());
}

Application::~Application()
{

    delete m_Framebuffer;

    for (auto it : m_Shaders)
    {
        glDeleteProgram(it.second);
    }

    for (auto it : m_Textures)
    {

        glDeleteTextures(1, (unsigned int *)&it.second);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

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