#pragma once

#include <glm/glm.hpp>

/**
 * @brief
 *
 */
enum class SAxis
{
    X,
    Y,
    Z
};

/**
 * @brief
 *
 */
struct STransform
{
    /**
     * @brief
     *
     */
    STransform()
        : position(0.0f)
        , scale(0.0f)
        , rotation(0.0f)
    {
    }

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    /**
     * @brief
     *
     * @param axis
     * @return glm::vec3
     */
    glm::vec3 get_scaled_axis(SAxis axis) const;

    /**
     * @brief
     *
     * @return glm::mat4
     */
    glm::mat4 get_transformation_matrix() const;
};