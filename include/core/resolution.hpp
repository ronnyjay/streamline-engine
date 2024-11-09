#pragma once

namespace engine
{

struct Resolution
{
    Resolution(int width, int height)
        : width(width)
        , height(height)
    {
    }

    int  width;
    int  height;

    bool operator<(const Resolution &other)
    {
        if (width != other.width)
            return width < other.width;

        return height < other.height;
    }

    bool operator==(const Resolution &other)
    {
        return width == other.width && height == other.height;
    }
};

} // namespace engine