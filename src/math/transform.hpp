#pragma once

#include "axis.hpp"

#include <glm/glm.hpp>

struct STransform
{
    STransform();

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    /**
     * @brief
     *
     * @param axis
     * @return
     */
    glm::vec3 get_scaled_axis(SAxis axis) const;

    /**
     * @brief
     *
     * @return glm::mat4
     */
    glm::mat4 get_transformation_matrix() const;
};