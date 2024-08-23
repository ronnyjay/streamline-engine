#include "window.hpp"

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

        bool overlap_x = x >= monitor->position_x && x < monitor->position_x + monitor->width;
        bool overlap_y = y >= monitor->position_y && y < monitor->position_y + monitor->height;

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
        set_display_mode(static_cast<display_mode>(display_mode_));
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

                primary_monitor_->resolution_fullscreen = i;
            }
        }

        if (!found)
        {
            primary_monitor_->resolution_fullscreen = -1;
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

                current_monitor_->resolution_windowed = i;
            }
        }

        if (!found)
        {
            current_monitor_->resolution_windowed = -1;
        }
    }
}

void window::set_display_mode(display_mode mode)
{
    // store the window's position and size
    if (last_display_mode_ == WINDOWED)
    {
        glfwGetWindowPos(window_, &x_, &y_);
        glfwGetWindowSize(window_, &last_width_, &last_height_);
    }

    if (mode == FULLSCREEN)
    {
        // get the primary monitor's current fullscreen resolution
        resolution current = primary_monitor_->resolutions[primary_monitor_->resolution_fullscreen];

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
        glfwSetWindowMonitor(
            window_, primary_monitor_->glfw_monitor, 0, 0, current.width, current.height, GLFW_DONT_CARE);
    }
    else if (mode == WINDOWED)
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
    else if (mode == BORDERLESS)
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