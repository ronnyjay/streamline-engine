#pragma once

namespace engine
{

struct CharacterComponent
{
    CharacterComponent() = default;

    /**
     * @brief
     *
     */
    float speed = 10.0f;

    /**
     * @brief
     *
     */
    float jump_height = 10.0f;
};

} // namespace engine