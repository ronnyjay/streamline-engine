#pragma once

#include <source_location>
#include <stdexcept>
#include <string>

class unimplemented_exception : public std::runtime_error
{
  public:
    unimplemented_exception(const std::source_location &location)
        : std::runtime_error(std::string(location.file_name()) + ":" + std::to_string(location.line()) + " - Unimplemented function.")
    {
    }
};
