#pragma once

#include <algorithm>
#include <tuple>

#include "setup.hpp"

namespace engine
{

STREAMLINE_INLINE std::tuple<int, int> reduce(int a, int b)
{
    int d = std::__gcd(a, b);

    a     = a / d;
    b     = b / d;

    return std::make_tuple(a, b);
}

} // namespace engine