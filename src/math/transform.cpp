#include "transform.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

glm::vec3 STransform::get_scaled_axis(SAxis axis) const
{
    glm::mat4 pitch = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 yaw = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 roll = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    switch (axis)
    {
    case SAxis::X:
        return glm::vec3(yaw * pitch * roll * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)) * scale.x;
        break;
    case SAxis::Y:
        return glm::vec3(yaw * pitch * roll * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)) * scale.y;
        break;
    case SAxis::Z:
        return glm::vec3(yaw * pitch * roll * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)) * scale.z;
        break;
    }

    return glm::vec3(0.0f);
}

glm::mat4 STransform::get_transformation_matrix() const
{
    return glm::translate(glm::mat4(1.0f), position) * glm::toMat4(glm::quat(rotation)) *
           glm::scale(glm::mat4(1.0f), scale);
}