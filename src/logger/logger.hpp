#pragma once

#include <string>

#define BGRN "\033[1;32m" // Bold Green text
#define BYEL "\033[1;33m" // Bold Yellow text
#define BRED "\033[1;31m" // Bold Red text
#define WHT "\033[1;97m"  // Bold White text

#define COLOR_RESET "\033[0m"

#define NWHT 1
#define GRN 3
#define YLW 4
#define CYN 5

class logger
{
  public:
    logger() = delete;

    static void info(const std::basic_string<char>, ...);
    static void warn(const std::basic_string<char>, ...);
    static void err(const std::basic_string<char>, ...);

    ~logger() = delete;

  private:
};
