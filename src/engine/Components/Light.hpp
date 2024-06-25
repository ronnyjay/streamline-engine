#pragma once

#include <glm/glm.hpp>

namespace engine
{

struct Light
{
    glm::vec4 color;
};

struct ShaderLight
{
    glm::vec4 position;
    Light properties;
};

}; // namespace engine