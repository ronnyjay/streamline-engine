#pragma once

#include <cstdio>
namespace engine
{

struct Resolution
{
    explicit Resolution(int width, int height)
        : width(width)
        , height(height)
    {
    }

    int  width;
    int  height;

    bool operator==(const Resolution &other) const
    {
        return width == other.width && height == other.height;
    }

    bool operator<(const Resolution &other) const
    {
        if (width != other.width)
        {
            return width < other.width;
        }

        return height < other.height;
    }

    const char *c_str() const
    {
        std::snprintf(format, sizeof(format), "%dx%d", width, height);
        return format;
    }

  private:
    mutable char format[32];
};

} // namespace engine