#include <engine/Window/window.hpp>

#include <engine/Application/Application.hpp>
#include <engine/InputManager/InputManager.hpp>
#include <engine/Json/json.hpp>
#include <engine/Logger/Logger.hpp>

using namespace engine;

const char *Window::display_modes_[] = {"Fullscreen", "Windowed", "Fullscreen Borderless"};

Window::Window(const std::filesystem::path &config, Application *const application)
{
    JSONObject json = JSON::parse(config);

    // if (json.contains("setting.defaultres"))
    // {
    //     settings_.defaultres = json.get<int>("setting.defaultres");
    // }

    // if (json.contains("setting.defaultresheight"))
    // {
    //     settings_.defaultresheight = json.get<int>("setting.defaultresheight");
    // }

    // if (json.contains("setting.displaymode"))
    // {
    //     settings_.displaymode = json.get<int>("setting.displaymode");
    // }

    // if (json.contains("setting.monitor"))
    // {
    //     settings_.monitor = json.get<int>("setting.monitor");
    // }
}

Window::Window(const int width, const int height, const char *title, Application *const application)
    : width_(width)
    , height_(height)
    , display_mode_(1)
    , last_width_(width)
    , last_height_(height)
    , last_display_mode_(1)
{
    // initialize window
    window_ = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window_)
    {
        Logger::Err("failed to create window\n");
        std::exit(EXIT_FAILURE);
    }

    // make this window's context the current of the main thread
    glfwMakeContextCurrent(window_);

    // lock aspect ratio
    glfwSetWindowAspectRatio(window_, width, height);

    // access the application's instance in glfw callbacks
    glfwSetWindowUserPointer(window_, application);

    // set window callbacks
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
    glfwSetWindowIconifyCallback(window_, minimize_callback);
    glfwSetWindowMaximizeCallback(window_, maximize_callback);
    glfwSetKeyCallback(window_, key_callback);
    glfwSetCursorPosCallback(window_, cursor_callback);
    glfwSetScrollCallback(window_, scroll_callback);

    // initialize with mouse hidden
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // initialize glad
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        Logger::Err("failed to initialize glad\n");
        std::exit(EXIT_FAILURE);
    }

    // initialize monitors
    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; ++i)
    {
        monitors_.emplace_back(new Monitor(monitors[i]));
    }

    // set monitor & resolution
    set_monitor(monitors_.at(0));

    refresh();

    set_resolution(Resolution(width, height));
}

void Window::refresh()
{
    int x, y;
    glfwGetWindowPos(window_, &x, &y);

    for (size_t i = 0; i < monitors_.size(); i++)
    {
        auto monitor = monitors_[i];

        bool overlap_x = x >= monitor->position_x && x < monitor->position_x + monitor->width;
        bool overlap_y = y >= monitor->position_y && y < monitor->position_y + monitor->height;

        if (overlap_x && overlap_y)
        {
            current_monitor_ = monitors_[i];
        }
    }

    current_monitor_ = primary_monitor_;
}

void Window::set_monitor(Monitor *monitor)
{
    primary_monitor_ = monitor;

    if (display_mode_ == Fullscreen || display_mode_ == Borderless)
    {
        set_display_mode(static_cast<DisplayMode>(display_mode_));
    }
}

void Window::set_resolution(Resolution res)
{
    if (display_mode_ == Fullscreen)
    {
        glfwSetWindowMonitor(window_, primary_monitor_->monitor, 0, 0, res.width, res.height, GLFW_DONT_CARE);

        bool found = false;

        for (size_t i = 0; i < primary_monitor_->resolutions.size(); ++i)
        {
            if (primary_monitor_->resolutions.at(i) == res)
            {
                found = true;

                primary_monitor_->resolution_fullscreen = i;
            }
        }

        if (!found)
        {
            primary_monitor_->resolution_fullscreen = -1;
        }
    }
    else if (display_mode_ == Windowed)
    {
        glfwSetWindowAspectRatio(window_, GLFW_DONT_CARE, GLFW_DONT_CARE); // remove aspect ratio lock
        glfwSetWindowSize(window_, res.width / current_monitor_->scale_x, res.height / current_monitor_->scale_y);
        glfwSetWindowAspectRatio(window_, res.width, res.height);

        bool found = false;

        for (size_t i = 0; i < current_monitor_->resolutions.size(); ++i)
        {
            if (current_monitor_->resolutions[i] == res)
            {
                found = true;

                current_monitor_->resolution_windowed = i;
            }
        }

        if (!found)
        {
            current_monitor_->resolution_windowed = -1;
        }
    }
}

void Window::set_display_mode(DisplayMode mode)
{
    // store the window's position and size
    if (last_display_mode_ == Windowed)
    {
        glfwGetWindowPos(window_, &x_, &y_);
        glfwGetWindowSize(window_, &last_width_, &last_height_);
    }

    if (mode == Fullscreen)
    {
        // get the primary monitor's current fullscreen resolution
        Resolution current = primary_monitor_->resolutions[primary_monitor_->resolution_fullscreen];

        // reset the window monitor
        glfwSetWindowMonitor(
            window_,
            nullptr,
            primary_monitor_->position_x,
            primary_monitor_->position_y,
            primary_monitor_->width,
            primary_monitor_->height,
            GLFW_DONT_CARE);

        // set the window monitor to the primary monitor
        glfwSetWindowMonitor(window_, primary_monitor_->monitor, 0, 0, current.width, current.height, GLFW_DONT_CARE);
    }
    else if (mode == Windowed)
    {
        // set window attributes
        if (!glfwGetWindowAttrib(window_, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(window_, GLFW_DECORATED, GL_TRUE);
        }

        if (glfwGetWindowAttrib(window_, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(window_, GLFW_FLOATING, GL_FALSE);
        }

        // restore window's last position and size
        glfwSetWindowMonitor(window_, nullptr, x_, y_, last_width_, last_height_, GLFW_DONT_CARE);
    }
    else if (mode == Borderless)
    {
        // set window attributes
        if (glfwGetWindowAttrib(window_, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(window_, GLFW_DECORATED, GL_FALSE);
        }

        if (!glfwGetWindowAttrib(window_, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(window_, GLFW_FLOATING, GL_TRUE);
        }

        // set the window monitor
        glfwSetWindowMonitor(
            window_,
            nullptr,
            primary_monitor_->position_x,
            primary_monitor_->position_y,
            primary_monitor_->width,
            primary_monitor_->height,
            GLFW_DONT_CARE);
    }

    // update last display mode
    last_display_mode_ = mode;
}

void Window::draw_debug_info()
{
    if (ImGui::TreeNode("Window"))
    {
        // draw monitor list
        if (display_mode_ == Windowed)
        {
            ImGui::BeginDisabled();
        }

        if (display_mode_ == Windowed)
        {
            ImGui::EndDisabled();
        }

        // draw resolution list
        if (display_mode_ == Borderless)
        {
            ImGui::BeginDisabled();
        }

        int *resolution_index;

        switch (display_mode_)
        {
        case Fullscreen:
            resolution_index = &current_monitor_->resolution_fullscreen;
            break;
        case Windowed:
            resolution_index = &current_monitor_->resolution_windowed;
            break;
        case Borderless:
            resolution_index = &current_monitor_->resolution_borderless;
            break;
        }

        if (ImGui::Combo(
                "Resolution",
                resolution_index,
                [](void *data, int index) -> const char *
                {
                    auto &list = *static_cast<std::vector<Resolution> *>(data);

                    if (index < 0 || index >= static_cast<int>(list.size()))
                    {
                        return nullptr;
                    }

                    return list[index].c_str();
                },
                static_cast<void *>(&current_monitor_->resolutions),
                current_monitor_->resolutions.size()))
        {
            set_resolution(current_monitor_->resolutions[*resolution_index]);
        }

        if (display_mode_ == Borderless)
        {
            ImGui::EndDisabled();
        }

        // draw display mode list
        if (ImGui::Combo("Display Mode", (int *)(&display_mode_), display_modes_, IM_ARRAYSIZE(display_modes_)))
        {
            set_display_mode(static_cast<DisplayMode>(display_mode_));
        }

        ImGui::TreePop();
    }
}

int Window::x()
{
    return x_;
}

int Window::y()
{
    return y_;
}

int Window::width()
{
    return width_;
}

int Window::height()
{
    return height_;
}

int Window::display_mode()
{
    return display_mode_;
}

Monitor *const Window::primary_monitor() const
{
    return primary_monitor_;
}

Monitor *const Window::current_monitor() const
{
    return current_monitor_;
}

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto *application = static_cast<Application *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
    {
        if (mods == GLFW_MOD_SHIFT)
        {
            application->Flags().ShowCursor = !application->Flags().ShowCursor;

            if (application->Flags().ShowCursor)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }

            application->Flags().FirstMouse = true;
        }
        else
        {
            application->Flags().ShowDebugWindow = !application->Flags().ShowDebugWindow;

            if (application->Flags().ShowDebugWindow)
            {
                if (!application->Flags().ShowCursor)
                {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }

                application->Flags().CaptureMouse = false;
            }
            else
            {
                if (!application->Flags().ShowCursor)
                {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }

                application->Flags().CaptureMouse = true;
            }
        }
    }

    InputManager::Instance().RegisterKeyState(key, scancode, action, mods);
}

void Window::cursor_callback(GLFWwindow *window, double xpos_in, double ypos_in)
{
    auto *application = static_cast<Application *>(glfwGetWindowUserPointer(window));

    static float lastX = application->Width() / 2.0f;
    static float lastY = application->Height() / 2.0f;

    if (!application->m_Flags.CaptureMouse)
    {
        return;
    }

    if (application->m_Flags.FirstMouse)
    {
        lastX = xpos_in;
        lastY = ypos_in;
        application->m_Flags.FirstMouse = false;
    }

    float xPos = static_cast<float>(xpos_in);
    float yPos = static_cast<float>(ypos_in);

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    if (application->m_CurrentCamera)
    {
        application->m_CurrentCamera->Move(xOffset, yOffset);
    }

    InputManager::Instance().RegisterCursorEvent(xOffset, yOffset);
}

void Window::scroll_callback(GLFWwindow *window, double x_offset, double y_offset)
{
    auto *application = static_cast<Application *>(glfwGetWindowUserPointer(window));

    if (application->m_Flags.ShowDebugWindow)
    {
        return;
    }

    if (application->m_CurrentCamera)
    {
        application->m_CurrentCamera->Move(y_offset);
    }

    InputManager::Instance().RegisterScrollEvent(x_offset, y_offset);
}

void Window::minimize_callback(GLFWwindow *window, int minimize)
{
    (minimize) ? glfwIconifyWindow(window) : glfwRestoreWindow(window);
}

void Window::maximize_callback(GLFWwindow *window, int maximize)
{
    (maximize) ? glfwMaximizeWindow(window) : glfwRestoreWindow(window);
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    auto *application = static_cast<Application *>(glfwGetWindowUserPointer(window));

    // application->m_Width = width;
    // application->m_Height = height;
}