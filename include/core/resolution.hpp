#pragma once

#include <format>

namespace engine
{

struct Resolution
{
    Resolution(int width, int height)
        : Width(width)
        , Height(height)
    {
    }

    int  Width;
    int  Height;

    bool operator==(const Resolution &other) const
    {
        return Width == other.Width && Height == other.Height;
    }

    bool operator<(const Resolution &other) const
    {
        if (Width != other.Width)
        {
            return Width < other.Width;
        }

        return Height < other.Height;
    }

    std::string ToString() const
    {
        return std::format("{}x{}", Width, Height);
    }
};

} // namespace engine