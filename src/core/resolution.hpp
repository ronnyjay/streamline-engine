#pragma once

namespace engine
{

struct Resolution
{
    Resolution(int width, int height) : Width(width), Height(height)
    {
    }

    int Width;
    int Height;

    bool operator<(const Resolution &other)
    {
        if (Width != other.Width)
            return Width < other.Width;

        return Height < other.Height;
    }

    bool operator==(const Resolution &other)
    {
        return Width == other.Width && Height == other.Height;
    }
};

} // namespace engine