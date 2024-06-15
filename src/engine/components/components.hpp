#pragma once

#include <entt/entt.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace engine
{

struct Light
{
  glm::vec4 color;
};

struct ShaderLight
{
  glm::vec4 pos;
  Light properties;
};

}; // namespace engine
