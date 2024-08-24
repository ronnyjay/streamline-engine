#pragma once

#define BGRN "\033[1;32m"
#define BYEL "\033[1;33m"
#define BRED "\033[1;31m"
#define BWHT "\033[1;97m"

#define COLOR_RESET "\033[0m"

#include <string>

struct logger
{
    explicit logger(const std::basic_string<char> &name)
        : component_name(name)
    {
    }

    void info(const std::basic_string<char>, ...);
    void warn(const std::basic_string<char>, ...);
    void err(const std::basic_string<char>, ...);

  private:
    const std::basic_string<char> component_name;
};
