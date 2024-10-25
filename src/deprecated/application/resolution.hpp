#pragma once

struct resolution
{
    resolution(int, int);
    resolution(const resolution &) = default;

    const bool operator==(const resolution &) const;
    const bool operator<(const resolution &) const;

    const char *c_str() const;

    int width;
    int height;

    mutable char format[32];
};
