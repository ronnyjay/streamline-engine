#include <engine/application/application.hpp>
#include <engine/stb/stb_image.hpp>
#include <engine/text/text.hpp>

using namespace engine;

Application::Application()
    : m_window(nullptr), m_camera(nullptr), m_world(nullptr), m_has_mouse(false), m_capture_mouse(false), m_show_wireframes(false),
      m_show_metrics(false), m_show_debug_window(false)
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

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
}

Window *const Application::window() const
{
    return m_window;
}

void Application::set_window(Window *const window)
{
    m_window = window;

    glfwSetFramebufferSizeCallback(m_window->glfw_window_ptr(), Application::framebuffer_size_callback);
    glfwSetWindowIconifyCallback(m_window->glfw_window_ptr(), Application::minimize_callback);
    glfwSetWindowMaximizeCallback(m_window->glfw_window_ptr(), Application::maximize_callback);
    glfwSetKeyCallback(m_window->glfw_window_ptr(), Application::key_callback);
    glfwSetCursorPosCallback(m_window->glfw_window_ptr(), Application::cursor_callback);
    glfwSetScrollCallback(m_window->glfw_window_ptr(), Application::scroll_callback);
    glfwSetWindowUserPointer(m_window->glfw_window_ptr(), this); // Access this object's instance in glfw callbacks

    // Setup Platform/Renderer backend
    // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplGlfw_InitForOpenGL(window->glfw_window_ptr(), true);
    ImGui_ImplOpenGL3_Init();
}

Camera *const Application::camera() const
{
    return m_camera;
}

void Application::add_camera(const int key, Camera *const camera)
{
    m_cameras.emplace(key, camera);

    if (m_camera == nullptr)
    {
        m_camera = camera;
    }
}

void Application::set_camera(const int key)
{
    auto camera_it = m_cameras.find(key);

    if (camera_it == m_cameras.end())
    {
        throw std::out_of_range("Camera not found");
    }

    m_camera = camera_it->second;
}

World *const Application::world() const
{
    return m_world;
}

void Application::add_world(const int key, World *const world)
{
    m_worlds.emplace(key, world);

    if (m_world == nullptr)
    {
        m_world = world;
    }
}

void Application::set_world(const int key)
{
    auto world_it = m_worlds.find(key);

    if (world_it == m_worlds.end())
    {
        throw std::out_of_range("World not found");
    }

    m_world = world_it->second;
}

void Application::bind_movement_key(const int key, const CameraDirection direction)
{
    m_keybinds.emplace(key, direction);
}

void Application::process_input()
{
    for (auto it = m_keybinds.begin(); it != m_keybinds.end(); ++it)
    {
        if (glfwGetKey(m_window->glfw_window_ptr(), it->first) == GLFW_PRESS)
        {
            m_camera->move(CameraDirection(it->second));
        }
    }

    if (glfwGetKey(m_window->glfw_window_ptr(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window->glfw_window_ptr(), GL_TRUE);
    }
}

void Application::toggle_wireframes()
{
    if (m_show_wireframes)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Application::set_camera_next()
{
    if (m_cameras.size() < 2)
    {
        return;
    }

    for (auto it = m_cameras.begin(); it != m_cameras.end(); ++it)
    {
        if (it->second == m_camera)
        {
            it++;

            if (it == m_cameras.end())
            {
                it = m_cameras.begin();
            }

            m_camera = it->second;
        }
    }
}

void Application::set_camera_previous()
{
    if (m_cameras.size() < 2)
    {
        return;
    }

    for (auto it = m_cameras.begin(); it != m_cameras.end(); ++it)
    {
        if (it->second == m_camera)
        {
            if (it == m_cameras.begin())
            {
                it = std::prev(m_cameras.end());
            }
            else
            {
                it = std::prev(it);
            }

            m_camera = it->second;
        }
    }
}

void Application::set_world_next()
{
    if (m_worlds.size() < 2)
    {
        return;
    }

    for (auto it = m_worlds.begin(); it != m_worlds.end(); ++it)
    {
        if (it->second == m_world)
        {
            it++;

            if (it == m_worlds.end())
            {
                it = m_worlds.begin();
            }

            m_world = it->second;
        }
    }
}

void Application::set_world_previous()
{
    if (m_worlds.size() < 2)
    {
        return;
    }

    for (auto it = m_worlds.begin(); it != m_worlds.end(); ++it)
    {
        if (it->second == m_world)
        {
            if (it == m_worlds.begin())
            {
                it = std::prev(m_worlds.end());
            }
            else
            {
                it = std::prev(it);
            }

            m_world = it->second;
        }
    }
}

void Application::run()
{
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    stbi_set_flip_vertically_on_load(true);

    double current_time;
    double last_time;
    double dt;

    last_time = current_time = glfwGetTime();

    while (m_window->running())
    {
        dt = (current_time = glfwGetTime()) - last_time;

        process_input();

        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_world->update(dt);
        m_world->draw();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (m_show_debug_window)
        {
            if (ImGui::Begin("Streamline Engine Debugger", &m_show_debug_window))
            {
                if (ImGui::Button("Show Metrics"))
                {
                    m_show_metrics = !m_show_metrics;
                }

                if (m_show_metrics)
                {
                    ImGui::ShowMetricsWindow();
                }

                if (ImGui::TreeNode("Debug"))
                {
                    ImGui::Text("Show Wireframes");
                    ImGui::SameLine();

                    if (ImGui::Checkbox("##wireframes", &m_show_wireframes))
                    {
                        toggle_wireframes();
                    }

                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("Camera"))
                {
                    ImGui::Text("Current:");
                    ImGui::SameLine();

                    if (ImGui::ArrowButton("Camera Previous", ImGuiDir_Left))
                    {
                        set_camera_previous();
                    }

                    ImGui::SameLine();
                    ImGui::TextUnformatted(m_camera->identifier().c_str());
                    ImGui::SameLine();

                    if (ImGui::ArrowButton("Camera Next", ImGuiDir_Right))
                    {
                        set_camera_next();
                    }

                    m_camera->draw_debug_info();

                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("World"))
                {
                    ImGui::Text("Current:");
                    ImGui::SameLine();

                    if (ImGui::ArrowButton("World Previous", ImGuiDir_Left))
                    {
                        set_world_previous();
                    }

                    ImGui::SameLine();
                    ImGui::TextUnformatted(m_world->identifier().c_str());
                    ImGui::SameLine();

                    if (ImGui::ArrowButton("World Next", ImGuiDir_Right))
                    {
                        set_world_next();
                    }

                    m_world->draw_debug_info();

                    ImGui::TreePop();
                }

                ImGui::End();
            }
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window->glfw_window_ptr());
        glfwPollEvents();

        last_time = current_time;
    }
}

Application::~Application()
{
    glfwTerminate();
}

void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    static_cast<Application *>(glfwGetWindowUserPointer(window))->m_window->resize(width, height);
}

void Application::minimize_callback(GLFWwindow *window, int minimize)
{
    static_cast<Application *>(glfwGetWindowUserPointer(window))->m_window->minimize(minimize);
}

void Application::maximize_callback(GLFWwindow *window, int maximize)
{
    static_cast<Application *>(glfwGetWindowUserPointer(window))->m_window->maximize(maximize);
}

void Application::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Application *application = static_cast<engine::Application *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
    {
        if (mods == GLFW_MOD_SHIFT)
        {
            if ((application->m_capture_mouse = !application->m_capture_mouse))
            {
                glfwSetInputMode(application->m_window->glfw_window_ptr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            else
            {
                glfwSetInputMode(application->m_window->glfw_window_ptr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
        else
        {
            application->m_show_debug_window = !application->m_show_debug_window;
        }
    }
}

void Application::cursor_callback(GLFWwindow *window, double xPosIn, double yPosIn)
{
    Application *application = static_cast<engine::Application *>(glfwGetWindowUserPointer(window));

    if (application->m_show_debug_window)
    {
        application->m_has_mouse = false;
        return;
    }

    if (!application->m_has_mouse)
    {
        application->m_cursor_x = xPosIn;
        application->m_cursor_y = yPosIn;
        application->m_has_mouse = true;
    }

    float xPos = static_cast<float>(xPosIn);
    float yPos = static_cast<float>(yPosIn);

    float xOffset = xPos - application->m_cursor_x;
    float yOffset = application->m_cursor_y - yPos;

    application->m_cursor_x = xPos;
    application->m_cursor_y = yPos;

    application->m_camera->move(xOffset, yOffset);
}

void Application::scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    static_cast<Application *>(glfwGetWindowUserPointer(window))->m_camera->move(yOffset);
}