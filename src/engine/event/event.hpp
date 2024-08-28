#pragma once

#include <sstream> // IWYU pragma: keep
#include <string>

#include <libstreamline/exception/exception.hpp>

// clang-format off
typedef enum 
{
    WindowResize, WindowMinimize, WindowMaximize,
    KeyPressed, KeyReleased, KeyRepeated,
    MouseButtonPressed, MouseMoved, MouseScrolled,
} event_type;
// clang-format on

class event
{
  public:
    virtual ~event() = default;

    virtual std::string to_string() const = 0;
};
