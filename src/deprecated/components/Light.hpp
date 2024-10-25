#pragma once

#include <glm/glm.hpp>

namespace engine
{

struct Light
{
    Light() = default;
    Light(const Light &) = default;

    Light(const glm::vec4 &lightColor)
        : color(lightColor)
    {
    }

    glm::vec4 color = glm::vec4(1.0f);
    glm::vec4 position = glm::vec4(0.0f);
};

} // namespace engine