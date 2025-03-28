#include "core/logger.hpp"

#include <cstdarg>

using namespace engine;

void Logger::info(std::string_view fmt, ...)
{
    va_list args;
    va_start(args, fmt);
#if 0
    printf(info_prefix.data());
#else
    printf("-- ");
#endif
    vprintf(fmt.data(), args);
    printf("\n");
    va_end(args);
}

void Logger::warn(std::string_view fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf(warn_prefix.data());
    vprintf(fmt.data(), args);
    printf("\n");
    va_end(args);
}

void Logger::fail(std::string_view fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf(fail_prefix.data());
    vprintf(fmt.data(), args);
    printf("\n");
    va_end(args);
}