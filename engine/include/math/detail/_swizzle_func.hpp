#pragma once

#define STREAMLINE_SWIZZLE_GEN_VEC2(T, A, B)                                                                           \
    vec<2, T> A##B()                                                                                                   \
    {                                                                                                                  \
        return vec<2, T>(this->A, this->B);                                                                            \
    }

#define STREAMLINE_SWIZZLE_GEN_VEC3(T, A, B, C)                                                                        \
    vec<3, T> A##B##C()                                                                                                \
    {                                                                                                                  \
        return vec<3, T>(this->A, this->B, this->C);                                                                   \
    }

#define STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, C, D)                                                                     \
    vec<4, T> A##B##C##D()                                                                                             \
    {                                                                                                                  \
        return vec<4, T>(this->A, this->B, this->C, this->D);                                                          \
    }

#define STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC2(T, A, B)                                                                 \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, A, A)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, A, B)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, B, A)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, B, B)

#define STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC2(T, A, B)                                                                 \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, A, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, A, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, B, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, B, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, A, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, A, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, B, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, B, B)

#define STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC2(T, A, B)                                                                 \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, B, B)

#define STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC3(T, A, B, C)                                                              \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, A, A)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, A, B)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, A, C)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, B, A)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, B, B)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, B, C)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, C, A)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, C, B)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, C, C)

#define STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC3(T, A, B, C)                                                              \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, A, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, A, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, A, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, B, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, B, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, B, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, C, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, C, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, C, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, A, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, A, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, A, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, B, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, B, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, B, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, C, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, C, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, C, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, A, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, A, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, A, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, B, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, B, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, B, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, C, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, C, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, C, C)

#define STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC3(T, A, B, C)                                                              \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, A, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, B, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, C, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, C, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, A, C, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, A, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, B, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, C, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, C, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, B, C, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, C, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, C, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, C, A, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, C, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, C, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, C, B, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, C, C, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, C, C, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, A, C, C, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, A, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, B, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, C, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, C, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, A, C, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, A, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, B, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, C, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, C, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, B, C, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, C, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, C, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, C, A, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, C, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, C, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, C, B, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, C, C, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, C, C, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, B, C, C, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, A, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, A, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, A, A, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, A, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, A, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, A, B, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, A, C, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, A, C, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, A, C, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, B, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, B, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, B, A, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, B, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, B, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, B, B, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, B, C, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, B, C, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, B, C, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, C, A, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, C, A, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, C, A, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, C, B, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, C, B, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, C, B, C)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, C, C, A)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, C, C, B)                                                                         \
    STREAMLINE_SWIZZLE_GEN_VEC4(T, C, C, C, C)

#define STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC4(T, A, B, C, D)                                                           \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, A, A)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, A, B)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, A, C)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, A, D)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, B, A)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, B, B)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, B, C)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, B, D)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, C, A)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, C, B)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, C, C)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, C, D)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, D, A)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, D, B)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, D, C)                                                                               \
    STREAMLINE_SWIZZLE_GEN_VEC2(T, D, D)

#define STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC4(T, A, B, C, D)                                                           \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, A, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, A, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, A, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, A, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, B, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, B, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, B, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, B, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, C, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, C, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, C, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, C, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, D, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, D, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, D, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, A, D, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, A, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, A, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, A, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, A, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, B, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, B, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, B, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, B, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, C, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, C, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, C, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, C, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, D, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, D, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, D, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, B, D, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, A, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, A, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, A, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, A, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, B, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, B, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, B, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, B, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, C, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, C, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, C, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, C, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, D, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, D, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, D, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, C, D, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, A, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, A, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, A, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, A, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, B, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, B, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, B, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, B, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, C, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, C, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, C, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, C, D)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, D, A)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, D, B)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, D, C)                                                                            \
    STREAMLINE_SWIZZLE_GEN_VEC3(T, D, D, D)

#define STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC4(T, A, B, C, D)
