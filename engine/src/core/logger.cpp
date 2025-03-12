#include "core/logger.hpp"

#include <cstdarg>

using namespace engine;

void logger::info(std::string_view fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf(info_prefix.data());
    vprintf(fmt.data(), args);
    printf("\n");
    va_end(args);
}

void logger::warn(std::string_view fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf(warn_prefix.data());
    vprintf(fmt.data(), args);
    printf("\n");
    va_end(args);
}

void logger::fail(std::string_view fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf(fail_prefix.data());
    vprintf(fmt.data(), args);
    printf("\n");
    va_end(args);
}