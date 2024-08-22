#include <engine/Resolution/resolution.hpp>

#include <cstdio>

using namespace engine;

Resolution::Resolution(int w, int h)
    : width(w)
    , height(h)
{
}

const bool Resolution::operator==(const Resolution &other) const
{
    return width == other.width && height == other.height;
}

const bool Resolution::operator<(const Resolution &other) const
{
    if (width != other.width)
    {
        return width < other.width;
    }

    return height < other.height;
}

const char *Resolution::c_str() const
{
    std::snprintf(format, sizeof(format), "%dx%d", width, height);

    return format;
}