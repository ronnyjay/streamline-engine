#pragma once

#include <string>

namespace engine
{

struct Identifier
{
  public:
    Identifier(const std::string &UUID)
        : identifier(UUID)
    {
    }

    Identifier(const Identifier &) = default;

    std::string identifier;
};

}; // namespace engine