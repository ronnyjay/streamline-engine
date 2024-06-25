#include <engine/Logger/Logger.hpp>

#include <stdarg.h>

using namespace engine;

void Logger::Info(const std::basic_string<char> format, ...)
{
    va_list args;
    va_start(args, format);

    const char *prefix = BWHT "[" BWHT "INFO" BWHT "] " COLOR_RESET;

    printf("%s", prefix);
    vprintf(format.c_str(), args);

    va_end(args);
}

void Logger::Warn(const std::basic_string<char> format, ...)
{
    va_list args;
    va_start(args, format);

    const char *prefix = BWHT "[" BYEL "WARN" BWHT "] " COLOR_RESET;

    printf("%s", prefix);
    vprintf(format.c_str(), args);

    va_end(args);
}

void Logger::Err(const std::basic_string<char> format, ...)
{
    va_list args;
    va_start(args, format);

    const char *prefix = BWHT "[" BRED "ERROR" BWHT "] " COLOR_RESET;

    printf("%s", prefix);
    vprintf(format.c_str(), args);
    va_end(args);
}
