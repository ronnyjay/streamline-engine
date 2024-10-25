#include "resolution.hpp"

#include <cstdio>

resolution::resolution(int w, int h)
    : width(w)
    , height(h)
{
}

const bool resolution::operator==(const resolution &other) const
{
    return width == other.width && height == other.height;
}

const bool resolution::operator<(const resolution &other) const
{
    if (width != other.width)
    {
        return width < other.width;
    }

    return height < other.height;
}

const char *resolution::c_str() const
{
    std::snprintf(format, sizeof(format), "%dx%d", width, height);

    return format;
}