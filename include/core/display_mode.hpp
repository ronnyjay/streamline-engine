#pragma once

#include <array>  // IWYU pragma: keep
#include <string> // IWYU pragma: keep

namespace engine
{

enum class WindowMode
{
    Windowed,
    Fullscreen,
    FullscreenBorderless
};

//
// String representations for UI, debug, etc.
//

// clang-format off
constexpr std::array<std::string_view, 3> WindowModeStrings = {
    "Windowed", 
    "Fullscreen", 
    "Fullscreen Borderless"
};
// clang-format on

} // namespace engine