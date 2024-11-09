#pragma once

#include <stdarg.h>
#include <string>

#include <memory>
#include <string>

// ANSI escape codes
#define BGRN "\033[1;32m"
#define BYEL "\033[1;33m"
#define BRED "\033[1;31m"
#define BWHT "\033[1;97m"

#define COLOR_RESET "\033[0m"

// TODO: The following definitions could be moved elsewhere.
//
// There is simply no place I can think of at the moment
// as this is really only used here.

// GCC/clang type names must be demangled
#ifdef __GNUG__
#include <cxxabi.h>

inline std::string Demangle(const char *type)
{
    //
    int status = 0;
    //

    std::unique_ptr<char, void (*)(void *)> type_name(abi::__cxa_demangle(type, nullptr, nullptr, &status), std::free);

    return (!status) ? type_name.get() : type;
}
// MVSC or other compilers will already be demangled
#else
inline std::string Demangle(const char *type)
{
    return std::string(type);
}
#endif

#define TYPENAME(T) Demangle(typeid(T).name())

namespace engine
{

class Logger
{
  public:
    Logger(const std::string &component)
        : mComponentName(component)
    {
    }

    void Info(const std::basic_string<char> format, ...)
    {
        va_list args;
        va_start(args, format);

        const char *prefix = BWHT "[" BGRN "  OK  " BWHT "]" COLOR_RESET;

        printf("%s %s - ", prefix, mComponentName.c_str());
        vprintf((format + "\n").c_str(), args);

        va_end(args);
    }

    void Warn(const std::basic_string<char> format, ...)
    {
        va_list args;
        va_start(args, format);

        const char *prefix = BWHT "[" BYEL " WARN " BWHT "]" COLOR_RESET;

        printf("%s %s - ", prefix, mComponentName.c_str());
        vprintf((format + "\n").c_str(), args);

        va_end(args);
    }

    void Error(const std::basic_string<char> format, ...)
    {
        va_list args;
        va_start(args, format);

        const char *prefix = BWHT "[" BRED "FAILED" BWHT "]" COLOR_RESET;

        printf("%s %s - ", prefix, mComponentName.c_str());
        vprintf((format + "\n").c_str(), args);
        va_end(args);
    }

  private:
    std::string mComponentName;
};

} // namespace engine