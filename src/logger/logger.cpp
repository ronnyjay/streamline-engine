#include <logger/logger.hpp>

#include <cstdarg>

void logger::info(const std::basic_string<char> format, ...)
{
    va_list args;
    va_start(args, format);

    const char *prefix = WHT "[" WHT "INFO" WHT "] " COLOR_RESET;

    printf("%s", prefix);
    vprintf(format.c_str(), args);

    va_end(args);
}

void logger::warn(const std::basic_string<char> format, ...)
{
    va_list args;
    va_start(args, format);

    const char *prefix = WHT "[" BYEL "WARN" WHT "] " COLOR_RESET;

    printf("%s", prefix);
    vprintf(format.c_str(), args);

    va_end(args);
}

void logger::err(const std::basic_string<char> format, ...)
{
    va_list args;
    va_start(args, format);

    const char *prefix = WHT "[" BRED "ERROR" WHT "] " COLOR_RESET;

    printf("%s", prefix);
    vprintf(format.c_str(), args);
    va_end(args);
}