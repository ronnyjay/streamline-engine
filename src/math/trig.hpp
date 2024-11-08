#pragma once

#include <cmath>

namespace engine::slm
{

/**
 * @brief
 *
 * @param degrees
 * @return float
 */
static float radians(float degrees)
{
    return degrees * (M_PI / 180);
}

/**
 * @brief
 *
 * @param radians
 * @return float
 */
static float degrees(float radians)
{
    return radians * (180 * M_1_PI);
}

}; // namespace engine::slm