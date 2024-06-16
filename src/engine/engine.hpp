#pragma once

#include <memory>
#include <string>

namespace engine
{

struct Loadable
{
    virtual ~Loadable()
    {
    }

    const std::string m_Path;

    virtual void Load(const std::basic_string<char> &path) = 0;
};

}; // namespace engine
