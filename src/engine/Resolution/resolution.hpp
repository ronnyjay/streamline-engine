#pragma once

namespace engine
{

struct Resolution
{
    Resolution(int, int);
    Resolution(const Resolution &) = default;

    const bool operator==(const Resolution &) const;
    const bool operator<(const Resolution &) const;

    const char *c_str() const;

    int width;
    int height;

    mutable char format[32];
};

} // namespace engine