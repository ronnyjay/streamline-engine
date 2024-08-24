#include "logger.hpp"

#include <stdarg.h>

void logger::info(const std::basic_string<char> format, ...)
{
    va_list args;
    va_start(args, format);

    const char *prefix = BWHT "[" BGRN "  OK  " BWHT "]" COLOR_RESET;

    printf("%s %s - ", prefix, component_name.c_str());
    vprintf((format + "\n").c_str(), args);

    va_end(args);
}

void logger::warn(const std::basic_string<char> format, ...)
{
    va_list args;
    va_start(args, format);

    const char *prefix = BWHT "[" BYEL " WARN " BWHT "]" COLOR_RESET;

    printf("%s %s - ", prefix, component_name.c_str());
    vprintf((format + "\n").c_str(), args);

    va_end(args);
}

void logger::err(const std::basic_string<char> format, ...)
{
    va_list args;
    va_start(args, format);

    const char *prefix = BWHT "[" BRED "FAILED" BWHT "]" COLOR_RESET;

    printf("%s %s - ", prefix, component_name.c_str());
    vprintf((format + "\n").c_str(), args);
    va_end(args);
}
