#include "transform.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

glm::vec3 Transform::get_scaled_axis(Axis axis) const
{
    switch (axis)
    {
    case Axis::X:
        return glm::vec3(rotation * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)) * scale.x;
        break;
    case Axis::Y:
        return glm::vec3(rotation * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)) * scale.y;
        break;
    case Axis::Z:
        return glm::vec3(rotation * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)) * scale.z;
        break;
    }

    return glm::vec3(0.0f);
}

glm::mat4 Transform::get_transformation_matrix() const
{
    return glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale);
}