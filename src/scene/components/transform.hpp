#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace engine
{

struct TransformComponent
{
    TransformComponent() = default;

    glm::mat4 transform() const
    {
        return glm::translate(glm::mat4(1.0f), translation) * glm::toMat4(glm::quat(rotation)) *
               glm::scale(glm::mat4(1.0f), scale);
    }

    glm::vec3 translation = {0.0f, 0.0f, 0.0f};
    glm::vec3 rotation    = {0.0f, 0.0f, 0.0f};
    glm::vec3 scale       = {1.0f, 1.0f, 1.0f};
};

} // namespace engine