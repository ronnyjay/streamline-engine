#pragma once

#include "singleton.hpp"

#include <filesystem>  // IWYU pragma: keep
#include <string_view> // IWYU pragma: keep

#define BRED "\033[1;31m"
#define BGRN "\033[1;32m"
#define BYEL "\033[1;33m"
#define BWHT "\033[1;37m"
#define COLOR_RESET "\033[0m"

namespace engine
{

class logger : public Singleton<logger>
{
    static constexpr std::string_view info_prefix = BWHT "[" BGRN "  OK  " BWHT "] " COLOR_RESET;
    static constexpr std::string_view warn_prefix = BWHT "[" BYEL " WARN " BWHT "] " COLOR_RESET;
    static constexpr std::string_view fail_prefix = BWHT "[" BRED "FAILED" BWHT "] " COLOR_RESET;

  public:
    static void info(std::string_view fmt, ...);
    static void warn(std::string_view fmt, ...);
    static void fail(std::string_view fmt, ...);
};

} // namespace engine