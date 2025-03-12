#pragma once

#include <cstdlib>  // IWYU pragma: keep
#include <iostream> // IWYU pragma: keep

#define STREAMLINE_GET_MACRO(_1, _2, NAME, ...) NAME

#define STREAMLINE_ASSERT_COND(condition)                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(condition))                                                                                              \
        {                                                                                                              \
            std::cerr << "Assertion `" #condition "` failed in " << __FUNCTION__ << " at " << __FILE__ << ":"          \
                      << __LINE__ << "." << std::endl;                                                                 \
            std::abort();                                                                                              \
        }                                                                                                              \
    } while (false)

#define STREAMLINE_ASSERT_MSG(condition, message)                                                                      \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(condition))                                                                                              \
        {                                                                                                              \
            std::cerr << "Assertion failed: (" << #condition << "), "                                                  \
                      << "function " << __FUNCTION__ << ", "                                                           \
                      << "file " << __FILE__ << ", "                                                                   \
                      << "line " << __LINE__ << ".\n"                                                                  \
                      << "Message: " << message << std::endl;                                                          \
            std::abort();                                                                                              \
        }                                                                                                              \
    } while (false)

#define STREAMLINE_ASSERT_LENGTH(index, length)                                                                        \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((index < 0) || (index >= length))                                                                          \
        {                                                                                                              \
            std::cerr << "Index `" #index "` out of bounds (length: `" #length "`) failed in " << __FUNCTION__         \
                      << " at " << __FILE__ << ":" << __LINE__ << "." << std::endl;                                    \
            std::abort();                                                                                              \
        }                                                                                                              \
    } while (false)

#define STREAMLINE_ASSERT(...)                                                                                         \
    STREAMLINE_GET_MACRO(__VA_ARGS__, STREAMLINE_ASSERT_MSG, STREAMLINE_ASSERT_COND)                                   \
    (__VA_ARGS__)
