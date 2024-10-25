#include "window.hpp"
#include "logger.hpp"

#include <algorithm>

using namespace engine;

Monitor::Monitor(GLFWmonitor *monitor, int number)
    : monitor(monitor)
    , m_monitor_number(number)
{
    title = glfwGetMonitorName(monitor);

    glfwGetMonitorWorkarea(monitor, &x, &y, &width, &height);
    glfwGetMonitorContentScale(monitor, &scale.x, &scale.y);

    int                count;
    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);

    for (int i = 0; i < count; i++)
    {
        resolutions.emplace_back(Resolution(modes[i].width, modes[i].height));
    }

    resolutions.erase(std::unique(resolutions.begin(), resolutions.end()), resolutions.end());

    resolution.fullscreen = resolutions.size() - 1;
    resolution.windowed   = -1;
    resolution.borderless = resolutions.size() - 1;
}

// clang-format off
const char *Window::DISPLAY_MODE_OPTIONS[] = {
    "Fullscreen","Windowed", "Fullscreen Borderless"
};
// clang-format on

Window::Window(int width, int height, const char *title)
    : m_Width(width)
    , mHeight(height)
{
    if (!glfwInit())
    {
        logger::err("Failed to initialize GLFW");
    }
    logger::info("Initialized GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    int           count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        Monitor monitor(monitors[i], i);

        logger::info("Loaded monitor: %s", monitor.title);
        logger::info("\tX: %dpx", monitor.x);
        logger::info("\tY: %dpx", monitor.y);
        logger::info("\tWidth: %dpx", monitor.width);
        logger::info("\tHeight: %dpx", monitor.height);
        logger::info("\tContent Scale X: %.2f", monitor.scale.x);
        logger::info("\tContent Scale Y: %.2f", monitor.scale.y);

        m_monitors.emplace_back(monitor);
    }

    m_primary_monitor = &m_monitors.at(0);
    m_current_monitor = &m_monitors.at(0);

    mWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    if (mWindow == nullptr)
    {
        logger::err("Failed to intialize window");
    }
    logger::info("Initialized window");

    glfwMakeContextCurrent(mWindow);

    glfwGetWindowPos(mWindow, &m_x, &m_y);
    glfwGetWindowSize(mWindow, &m_Width, &mHeight);

    glfwSetWindowUserPointer(mWindow, this);
    glfwSetWindowAspectRatio(mWindow, width, height);

    glfwSetFramebufferSizeCallback(mWindow, Window::framebuffer_size_callback);
    glfwSetWindowIconifyCallback(mWindow, Window::minimize_callback);
    glfwSetWindowMaximizeCallback(mWindow, Window::maximize_callback);
    glfwSetKeyCallback(mWindow, Window::key_callback);
    glfwSetMouseButtonCallback(mWindow, Window::mouse_callback);
    glfwSetCursorPosCallback(mWindow, Window::cursor_pos_callback);
    glfwSetScrollCallback(mWindow, Window::scroll_callback);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        logger::err("Failed to initialize glad");
    }

    // apply window settings
    // these should be coming from a configuration
    set_display_mode(WINDOWED);

    // resolution must be set as setting
    // display mode does not update index
    set_resolution(width, height);
}

void Window::refresh()
{
    int x, y;
    glfwGetWindowPos(mWindow, &x, &y);

    for (auto &monitor : m_monitors)
    {
        bool overlap_x = x >= monitor.x && x < monitor.x + monitor.width;
        bool overlap_y = y >= monitor.y && y < monitor.y + monitor.height;

        if (overlap_x && overlap_y && monitor != *m_current_monitor)
        {
            m_current_monitor = &monitor;

            if (m_display_mode == WINDOWED)
            {
                set_resolution(m_width, m_height);
            }
        }
    }
}

void Window::set_monitor(int monitor)
{
    if (monitor < 0 || static_cast<size_t>(monitor) >= m_monitors.size())
    {
        return;
    }

    m_primary_monitor = &m_monitors.at(monitor);

    if (m_display_mode != WINDOWED)
    {
        set_display_mode(static_cast<DisplayMode>(m_display_mode));
    }
}

void Window::set_resolution(int width, int height)
{
    if (m_display_mode == BORDERLESS)
    {
        return;
    }

    if (m_display_mode == FULLSCREEN)
    {
        glfwSetWindowMonitor(mWindow, m_primary_monitor->monitor, 0, 0, width, height, GLFW_DONT_CARE);

        for (size_t i = 0; i < m_primary_monitor->resolutions.size(); i++)
        {
            if (Resolution(width, height) == m_primary_monitor->resolutions.at(i))
            {
                m_primary_monitor->resolution.fullscreen = i;

                return;
            }
        }

        m_primary_monitor->resolution.fullscreen = -1;
    }

    if (m_display_mode == WINDOWED)
    {
        m_Width = width;
        mHeight = height;

        auto monitor_scale = m_current_monitor->scale;

        glfwSetWindowAspectRatio(mWindow, GLFW_DONT_CARE, GLFW_DONT_CARE);
        glfwSetWindowSize(mWindow, width / monitor_scale.x, height / monitor_scale.y);
        glfwSetWindowAspectRatio(mWindow, width, height);

        for (size_t i = 0; i < m_current_monitor->resolutions.size(); i++)
        {
            if (Resolution(width, height) == m_current_monitor->resolutions.at(i))
            {
                m_current_monitor->resolution.windowed = i;

                return;
            }
        }

        m_current_monitor->resolution.windowed = -1;
    }
}

void Window::set_display_mode(DisplayMode mode)
{
    if (m_display_mode == WINDOWED)
    {
        glfwGetWindowPos(mWindow, &m_x, &m_y);
    }

    if (mode == FULLSCREEN)
    {
        Resolution current = m_primary_monitor->resolutions[m_primary_monitor->resolution.fullscreen];

        glfwSetWindowMonitor(
            mWindow,
            nullptr,
            m_primary_monitor->x,
            m_primary_monitor->y,
            m_primary_monitor->width,
            m_primary_monitor->height,
            0);

        glfwSetWindowMonitor(mWindow, m_primary_monitor->monitor, 0, 0, current.width, current.height, GLFW_DONT_CARE);
    }

    if (mode == BORDERLESS)
    {
        if (glfwGetWindowAttrib(mWindow, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GL_FALSE);
        }

        if (!glfwGetWindowAttrib(mWindow, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(mWindow, GLFW_FLOATING, GL_TRUE);
        }

        glfwSetWindowMonitor(
            mWindow,
            nullptr,
            m_primary_monitor->x,
            m_primary_monitor->y,
            m_primary_monitor->width,
            m_primary_monitor->height,
            0);
    }

    if (mode == WINDOWED)
    {
        if (!glfwGetWindowAttrib(mWindow, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GL_TRUE);
        }

        if (glfwGetWindowAttrib(mWindow, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(mWindow, GLFW_FLOATING, GL_FALSE);
        }

        glfwSetWindowMonitor(mWindow, nullptr, m_x, m_y, m_width, m_height, 0);
    }

    m_display_mode = mode;
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    static_cast<Window *>(glfwGetWindowUserPointer(window))
        ->dispatch(WindowResized, FramebufferResizeEvent(width, height));
}

void Window::minimize_callback(GLFWwindow *window, int minimized)
{
    (minimized) ? glfwIconifyWindow(window) : glfwRestoreWindow(window);
}

void Window::maximize_callback(GLFWwindow *window, int maximized)
{
    (maximized) ? glfwMaximizeWindow(window) : glfwRestoreWindow(window);
}

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    static_cast<Window *>(glfwGetWindowUserPointer(window))
        ->dispatch(KeyPressed, KeyPressEvent(key, scancode, action, mods));
}

void Window::mouse_callback(GLFWwindow *window, int button, int action, int mods)
{
    static_cast<Window *>(glfwGetWindowUserPointer(window))
        ->dispatch(MousePressed, MousePressEvent(button, action, mods));
}

void Window::cursor_pos_callback(GLFWwindow *window, double xpos, double ypos)
{
    static_cast<Window *>(glfwGetWindowUserPointer(window))->dispatch(MouseMoved, MouseMoveEvent(xpos, ypos));
}

void Window::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    static_cast<Window *>(glfwGetWindowUserPointer(window))
        ->dispatch(MouseScrolled, MouseScrollEvent(xoffset, yoffset));
}

void Window::on_debug()
{
    if (ImGui::TreeNode("Window"))
    {
        // Video related window settings
        //
        // These also belong in a settings menu provided by the game

        ImGui::Separator();
        ImGui::Text("Video");
        ImGui::Separator();

        // Selecting a monitor has no effect here, disable.
        if (m_display_mode == WINDOWED)
        {
            ImGui::BeginDisabled();
        }

        int m_index = m_primary_monitor->number();

        if (ImGui::Combo(
                "Monitor",
                &m_index,
                [](void *data, int index) -> const char *
                {
                    auto &v = *static_cast<std::vector<Monitor> *>(data);
                    if (index < 0 || index >= static_cast<int>(v.size()))
                    {
                        return nullptr;
                    }
                    return v[index].title;
                },
                &m_monitors,
                m_monitors.size()))
        {
            set_monitor(m_index);
        }

        if (m_display_mode == WINDOWED)
        {
            ImGui::EndDisabled();
        }

        // Selecting a resolution has no effect here, disable.
        if (m_display_mode == BORDERLESS)
        {
            ImGui::BeginDisabled();
        }

        int r_index;

        switch (m_display_mode)
        {
        case FULLSCREEN:
            r_index = m_current_monitor->resolution.fullscreen;
            break;
        case WINDOWED:
            r_index = m_current_monitor->resolution.windowed;
            break;
        case BORDERLESS:
            r_index = m_current_monitor->resolution.borderless;
            break;
        }

        if (ImGui::Combo(
                ("Window size"),
                &r_index,
                [](void *data, int index) -> const char *
                {
                    auto &v = *static_cast<std::vector<Resolution> *>(data);
                    if (index < 0 || index >= static_cast<int>(v.size()))
                    {
                        return nullptr;
                    }
                    return v[index].c_str();
                },
                &m_current_monitor->resolutions,
                m_current_monitor->resolutions.size()))
        {
            set_resolution(
                m_current_monitor->resolutions[r_index].width, m_current_monitor->resolutions[r_index].height);
        }

        if (m_display_mode == BORDERLESS)
        {
            ImGui::EndDisabled();
        }

        int mode = m_display_mode;

        if (ImGui::Combo("Display mode", &mode, DISPLAY_MODE_OPTIONS, IM_ARRAYSIZE(DISPLAY_MODE_OPTIONS)))
        {
            set_display_mode(static_cast<DisplayMode>(mode));
        }

        // Information relating the monitor's current state
        //
        // The position of the window is retrieved manually here
        // as the stored coordinates are only updated on display mode changes

        ImGui::Separator();
        ImGui::Text("Diagnostics");
        ImGui::Separator();

        int x, y;
        glfwGetWindowPos(mWindow, &x, &y);

        ImGui::Text("X: %d", x);
        ImGui::Text("Y: %d", y);
        ImGui::Text("Width: %d", m_width);
        ImGui::Text("Height: %d", m_height);
        ImGui::Text("Primary monitor: %s", m_primary_monitor->title);
        ImGui::Text("Current monitor: %s", m_current_monitor->title);

        for (auto &monitor : m_monitors)
        {
            ImGui::Text("Monitor %d: %s", monitor.number(), monitor.title);
        }

        // These are just some of the window attributes made available by glfw.
        //
        // There are many, many more defined that could be used but are not
        // necessary at this time.

        ImGui::Separator();
        ImGui::Text("Attributes");
        ImGui::Separator();

        ImGui::Text("Focused: %s", glfwGetWindowAttrib(m_window, GLFW_DECORATED) ? "TRUE" : "FALSE");
        ImGui::Text("Resizable: %s", glfwGetWindowAttrib(m_window, GLFW_RESIZABLE) ? "TRUE" : "FALSE");
        ImGui::Text("Decorated: %s", glfwGetWindowAttrib(m_window, GLFW_DECORATED) ? "TRUE" : "FALSE");
        ImGui::Text("Floating: %s", glfwGetWindowAttrib(m_window, GLFW_FLOATING) ? "TRUE" : "FALSE");
        ImGui::Text("Maximized: %s", glfwGetWindowAttrib(m_window, GLFW_DECORATED) ? "TRUE" : "FALSE");
        ImGui::Text("Hovered: %s", glfwGetWindowAttrib(m_window, GLFW_HOVERED) ? "TRUE" : "FALSE");

        ImGui::Separator();
        ImGui::TreePop();
    }
}
