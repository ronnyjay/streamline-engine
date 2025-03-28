#pragma once

namespace engine
{

struct GameInstance
{
    GameInstance(const char *title)
        : title(title)
    {
    }

    const char *title;
};

} // namespace engine