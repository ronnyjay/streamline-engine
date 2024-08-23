#include "window.hpp"
#include "application.hpp"

#include "engine/event/event.hpp" // IWYU pragma: keep

const std::string window::display_modes_strings[] = {"Fullscreen", "Windowed", "Fullscreen Borderless"};

window::window(const config &cfg) // todo: potentially change this
    : width_(cfg.defaultres)
    , height_(cfg.defaultresheight)
    , display_mode_(cfg.displaymode)
{
    // initialize glfw
    if (!glfwInit())
    {
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // initialize window
    window_ = glfwCreateWindow(width_, height_, "Streamline Engine", NULL, NULL);

    if (!window_)
    {
        std::exit(EXIT_FAILURE);
    }

    // make this window's context the current of the main thread
    glfwMakeContextCurrent(window_);
}

void window::refresh()
{
    int x, y;
    glfwGetWindowPos(window_, &x, &y);

    for (size_t i = 0; i < monitors_.size(); i++)
    {
        auto monitor = monitors_[i];

        bool overlap_x = x >= monitor->x && x < monitor->x + monitor->width;
        bool overlap_y = y >= monitor->y && y < monitor->y + monitor->height;

        if (overlap_x && overlap_y)
        {
            current_monitor_ = monitors_[i];
        }
    }

    current_monitor_ = primary_monitor_;
}

void window::set_monitor(monitor *monitor)
{
    primary_monitor_ = monitor;

    if (display_mode_ == FULLSCREEN || display_mode_ == BORDERLESS)
    {
        set_display_mode(static_cast<display_mode_e>(display_mode_));
    }
}

void window::set_resolution(resolution res)
{
    if (display_mode_ == FULLSCREEN)
    {
        glfwSetWindowMonitor(window_, primary_monitor_->glfw_monitor, 0, 0, res.width, res.height, GLFW_DONT_CARE);

        bool found = false;

        for (size_t i = 0; i < primary_monitor_->resolutions.size(); ++i)
        {
            if (primary_monitor_->resolutions.at(i) == res)
            {
                found = true;

                primary_monitor_->active_resolutions.fullscreen = i;
            }
        }

        if (!found)
        {
            primary_monitor_->active_resolutions.fullscreen = -1;
        }
    }
    else if (display_mode_ == WINDOWED)
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

                current_monitor_->active_resolutions.windowed = i;
            }
        }

        if (!found)
        {
            current_monitor_->active_resolutions.windowed = -1;
        }
    }
}

void window::set_display_mode(display_mode_e mode)
{
    // store window's position and size
    if (last_display_mode_ == WINDOWED)
    {
        glfwGetWindowPos(window_, &x_, &y_);
        glfwGetWindowSize(window_, &last_width_, &last_height_);
    }

    if (mode == FULLSCREEN)
    {
        resolution current = primary_monitor_->resolutions[primary_monitor_->active_resolutions.fullscreen];

        // set monitor null before setting to primary
        // ... fixes issues with linux
        glfwSetWindowMonitor(
            window_,
            nullptr,
            primary_monitor_->x,
            primary_monitor_->y,
            primary_monitor_->width,
            primary_monitor_->height,
            GLFW_DONT_CARE);

        glfwSetWindowMonitor(
            window_, primary_monitor_->glfw_monitor, 0, 0, current.width, current.height, GLFW_DONT_CARE);
    }
    else if (mode == WINDOWED)
    {
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
    else if (mode == BORDERLESS)
    {
        if (glfwGetWindowAttrib(window_, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(window_, GLFW_DECORATED, GL_FALSE);
        }

        if (!glfwGetWindowAttrib(window_, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(window_, GLFW_FLOATING, GL_TRUE);
        }

        glfwSetWindowMonitor(
            window_,
            nullptr,
            primary_monitor_->x,
            primary_monitor_->y,
            primary_monitor_->width,
            primary_monitor_->height,
            GLFW_DONT_CARE);
    }

    last_display_mode_ = mode;
}

void window::key_callback(GLFWwindow *, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        application::get().on_event(window_close_event());
    }
}

void window::cursor_callback(GLFWwindow *, double xpos_in, double ypos_in)
{
}

void window::scroll_callback(GLFWwindow *, double x_offset, double y_offset)
{
}

static void minimize_callback(GLFWwindow *, int minimize)
{
}

static void maximize_callback(GLFWwindow *, int maximize)
{
}

static void framebuffer_size_callback(GLFWwindow *, int width, int height)
{
    application::get().on_event(window_resize_event(width, height));
}