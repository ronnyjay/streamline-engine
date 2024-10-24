#pragma once

#include <string>

namespace engine
{

struct IDComponent
{
    IDComponent(const std::string &id)
        : id(id)
    {
    }

    std::string id;
};

} // namespace engine