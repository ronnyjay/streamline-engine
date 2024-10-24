#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

/**
 * @brief
 *
 */
enum class Axis
{
    X,
    Y,
    Z
};

/**
 * @brief
 *
 */
struct Transform
{
    /**
     * @brief
     *
     */
    Transform()
        : position(0.0f)
        , scale(0.0f)
    {
        rotation = glm::quat(1.0f, glm::vec3(0.0f));
    }

    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;

    /**
     * @brief
     *
     * @param axis
     * @return glm::vec3
     */
    glm::vec3 get_scaled_axis(Axis axis) const;

    /**
     * @brief
     *
     * @return glm::mat4
     */
    glm::mat4 get_transformation_matrix() const;
};