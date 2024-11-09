#pragma once

#include <source_location>
#include <stdexcept>
#include <string>

namespace engine
{

class EngineException
{
};

class UnimplementedException : public std::runtime_error
{
  public:
    UnimplementedException(const std::source_location &location)
        : std::runtime_error(
              std::string(location.file_name()) + ":" + std::to_string(location.line()) + " - unimplemented function.")
    {
    }
};

class PlatformInitializationException : public std::runtime_error
{
  public:
    PlatformInitializationException(const std::string &message, const std::source_location &location)
        : std::runtime_error(
              std::string(location.file_name()) + ":" + std::to_string(location.line()) + " - " + message)
    {
    }
};

class MissingResourceException : public std::runtime_error
{
  public:
    MissingResourceException(const std::string &id, const std::source_location &location)
        : std::runtime_error(
              std::string(location.file_name()) + ":" + std::to_string(location.line()) + " - missing resource: " + id)
    {
    }
};

} // namespace engine