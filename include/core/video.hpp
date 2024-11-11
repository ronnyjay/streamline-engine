#pragma once

/*** @brief Type definitions and string representations for core video components */

#include <array>  // IWYU pragma: keep
#include <format>
#include <string> // IWYU pragma: keep

namespace engine
{

enum class WindowMode
{
    Windowed,
    Fullscreen,
    FullscreenBorderless
};

// clang-format off
constexpr std::array<std::string_view, 3> WindowModeStrings = {
    "Windowed", 
    "Fullscreen", 
    "Fullscreen Borderless"
};
// clang-format on

enum class AspectRatio
{
    Automatic,
    Standard_4_3,
    Standard_5_4,
    Wide_16_9,
    Wide_16_10,
    Ultrawide_21_9,
    Ultrawide_32_9
};

// clang-format off
constexpr std::array<std::string_view, 7> AspectRatioStrings = {
    "Automatic",
    "Standard 4:3", 
    "Standard 5:4",
    "Wide 16:9", 
    "Wide 16:10",
    "Ultrawide 21:9", 
    "Ultrawide 32:9"
};
// clang-format on

/** @brief Wrapper for a display's refresh rate; provides ToString functionality  */
struct RefreshRate
{
    /** @brief Default constructor */
    RefreshRate(int rate)
        : rate(rate)
    {
    }

    int rate;

    /** @brief operator== overload for std::unique filter */
    bool operator==(const RefreshRate &other) const
    {
        return rate == other.rate;
    }

    /** @brief Returns a string representation of the refresh rate */
    std::string ToString() const
    {
        return std::format("{:2f} hz", static_cast<float>(rate));
    }
};

/** @brief Wrapper for a display's resolution; provides ToString functionality  */
struct Resolution
{
    /** @brief Default constructor */
    Resolution(int width, int height)
        : width(width)
        , height(height)
    {
    }

    int width;
    int height;

    /** @brief operator== overload for std::unique filter */
    bool operator==(const Resolution &other)
    {
        return width == other.width && height == other.height;
    }

    /** @brief Returns a string representation of the resolution */
    std::string ToString() const
    {
        return std::format("{}x{}", width, height);
    }
};

}; // namespace engine