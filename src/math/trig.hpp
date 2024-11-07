#pragma once

#include <cmath>

namespace engine::math
{

/**
 * @brief
 *
 * @param degrees
 * @return float
 */
static float ToRadians(float degrees)
{
    return degrees * (M_PI / 180);
}

/**
 * @brief
 *
 * @param radians
 * @return float
 */
static float ToDegrees(float radians)
{
    return radians * (180 * M_1_PI);
}

}; // namespace engine::math