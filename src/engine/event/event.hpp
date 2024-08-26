#pragma once

#include <string>

#include <functional> // IWYU pragma: keep
#include <sstream>    // IWYU pragma: keep

#include <libstreamline/exception/exception.hpp>

#define STREAMLINE_MAKE_CALLBACK(type) typedef std::function<void(type)> callback
#define STREAMLINE_MAKE_CALLBACK_EXPLICIT(type) typedef std::function<void(type)> type##_callback

class event
{
  public:
    virtual ~event() = default;

    virtual std::string to_string() const = 0;
};
