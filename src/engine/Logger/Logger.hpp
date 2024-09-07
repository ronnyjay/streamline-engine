#pragma once

#define BGRN "\033[1;32m"
#define BYEL "\033[1;33m"
#define BRED "\033[1;31m"
#define BWHT "\033[1;97m"

#define COLOR_RESET "\033[0m"

#include <string>

namespace engine
{

struct Logger
{
    Logger()
    {
    }

    static void info(const std::basic_string<char>, ...);
    static void warn(const std::basic_string<char>, ...);
    static void err(const std::basic_string<char>, ...);
};

} // namespace engine