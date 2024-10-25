#pragma once

#include "event.hpp"

#include <libstreamline/exception/exception.hpp>

class window_resize_event : public event
{
  public:
    window_resize_event(const int width, const int height)
        : m_width(width)
        , m_height(height)
    {
    }

    int width() const
    {
        return m_width;
    }

    int height() const
    {
        return m_height;
    }

    std::string to_string() const override
    {
        return (std::stringstream() << "Window resized: " << m_width << 'x' << m_height).str();
    }

  private:
    int m_width;
    int m_height;
};

class window_minimize_event : public event
{
  public:
    window_minimize_event(int minimized)
        : m_minimized(minimized)
    {
    }

    bool minimized() const
    {
        return static_cast<bool>(m_minimized);
    }

    std::string to_string() const override
    {
        throw unimplemented_exception(std::source_location::current());
    }

  private:
    int m_minimized;
};

class window_maximize_event : public event
{
  public:
    window_maximize_event(int maximized)
        : m_maximized(maximized)
    {
    }

    bool maximized() const
    {
        return static_cast<bool>(m_maximized);
    }

    std::string to_string() const override
    {
        throw unimplemented_exception(std::source_location::current());
    }

  private:
    int m_maximized;
};