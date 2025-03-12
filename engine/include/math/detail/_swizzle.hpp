#pragma once

namespace engine
{

template <int N, typename T>
struct vec;

template <typename T, int N>
struct _swizzle_base
{
    char _buffer[1];

    T &elem(int i)
    {
        return (reinterpret_cast<T *>(_buffer))[i];
    }

    T const &elem(int i) const
    {
        return (reinterpret_cast<const T *>(_buffer))[i];
    }
};

template <typename T, int N, int E0, int E1, int E3, int E4>
struct _swizzle : public _swizzle_base<T, N>
{
};

template <typename T, int E0, int E1>
struct _swizzle<T, 2, E0, E1, -1, -2> : _swizzle_base<T, 2>
{
    vec<2, T> operator()() const
    {
        return vec<2, T>(this->elem(E0), this->elem(E1));
    }
};

template <typename T, int E0, int E1, int E2>
struct _swizzle<T, 3, E0, E1, E2, 3> : _swizzle_base<T, 3>
{
    vec<3, T> operator()() const
    {
        return vec<3, T>(this->elem(E0), this->elem(E1), this->elem(E2));
    }
};

template <typename T, int E0, int E1, int E2, int E3>
struct _swizzle<T, 4, E0, E1, E2, E3> : _swizzle_base<T, 4>
{
    vec<4, T> operator()() const
    {
        return vec<4, T>(this->elem(E0), this->elem(E1), this->elem(E2), this->elem(E3));
    }
};

} // namespace engine

#define STREAMLINE_SWIZZLE2_2MEMBERS(T, E0, E1)                                                                        \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 0, 0, -1, -2> E0##E0;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 0, 1, -1, -2> E0##E1;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 1, 0, -1, -2> E1##E0;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 1, 2, -1, -2> E1##E1;                                                                           \
    };

#define STREAMLINE_SWIZZLE2_3MEMBERS(T, E0, E1)                                                                        \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 0, 0, 3> E0##E0##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 0, 1, 3> E0##E0##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 1, 0, 3> E0##E1##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 1, 1, 3> E0##E1##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 0, 0, 3> E1##E0##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 0, 1, 3> E1##E0##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 1, 0, 3> E1##E1##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 1, 1, 3> E1##E1##E1;                                                                         \
    };

#define STREAMLINE_SWIZZLE2_4MEMBERS(T, E0, E1)                                                                        \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 0> E0##E0##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 1> E0##E0##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 0> E0##E0##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 1> E0##E0##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 0> E0##E1##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 1> E0##E1##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 0> E0##E1##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 1> E0##E1##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 0> E1##E0##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 1> E1##E0##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 0> E1##E0##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 1> E1##E0##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 0> E1##E1##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 1> E1##E1##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 0> E1##E1##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 1> E1##E1##E1##E1;                                                                     \
    };

#define STREAMLINE_SWIZZLE3_2MEMBERS(T, E0, E1, E2)                                                                    \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 0, 0, -1, -2> E0##E0;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 0, 1, -1, -2> E0##E1;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 0, 2, -1, -2> E0##E2;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 1, 0, -1, -2> E1##E0;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 1, 1, -1, -2> E1##E1;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 1, 2, -1, -2> E1##E2;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 2, 0, -1, -2> E2##E0;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 2, 1, -1, -2> E2##E1;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 2, 2, -1, -2> E2##E2;                                                                           \
    };

#define STREAMLINE_SWIZZLE3_3MEMBERS(T, E0, E1, E2)                                                                    \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 0, 0, 3> E0##E0##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 0, 1, 3> E0##E0##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 0, 2, 3> E0##E0##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 1, 0, 3> E0##E1##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 1, 1, 3> E0##E1##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 1, 2, 3> E0##E1##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 2, 0, 3> E0##E2##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 2, 1, 3> E0##E2##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 2, 2, 3> E0##E2##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 0, 0, 3> E1##E0##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 0, 1, 3> E1##E0##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 0, 2, 3> E1##E0##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 1, 0, 3> E1##E1##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 1, 1, 3> E1##E1##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 1, 2, 3> E1##E1##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 2, 0, 3> E1##E2##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 2, 1, 3> E1##E2##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 2, 2, 3> E1##E2##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 0, 0, 3> E2##E0##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 0, 1, 3> E2##E0##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 0, 2, 3> E2##E0##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 1, 0, 3> E2##E1##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 1, 1, 3> E2##E1##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 1, 2, 3> E2##E1##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 2, 0, 3> E2##E2##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 2, 1, 3> E2##E2##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 2, 2, 3> E2##E2##E2;                                                                         \
    };

#define STREAMLINE_SWIZZLE3_4MEMBERS(T, E0, E1, E2)                                                                    \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 0> E0##E0##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 1> E0##E0##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 2> E0##E0##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 0> E0##E0##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 1> E0##E0##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 2> E0##E0##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 2, 0> E0##E0##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 2, 1> E0##E0##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 2, 2> E0##E0##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 0> E0##E1##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 1> E0##E1##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 2> E0##E1##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 0> E0##E1##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 1> E0##E1##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 2> E0##E1##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 2, 0> E0##E1##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 2, 1> E0##E1##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 2, 2> E0##E1##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 0, 0> E0##E2##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 0, 1> E0##E2##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 0, 2> E0##E2##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 1, 0> E0##E2##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 1, 1> E0##E2##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 1, 2> E0##E2##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 2, 0> E0##E2##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 2, 1> E0##E2##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 2, 2> E0##E2##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 0, 0> E1##E0##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 0, 1> E1##E0##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 0, 2> E1##E0##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 1, 0> E1##E0##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 1, 1> E1##E0##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 1, 2> E1##E0##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 2, 0> E1##E0##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 2, 1> E1##E0##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 2, 2> E1##E0##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 0, 0> E1##E1##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 0, 1> E1##E1##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 0, 2> E1##E1##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 1, 0> E1##E1##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 1, 1> E1##E1##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 1, 2> E1##E1##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 2, 0> E1##E1##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 2, 1> E1##E1##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 2, 2> E1##E1##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 0, 0> E1##E2##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 0, 1> E1##E2##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 0, 2> E1##E2##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 1, 0> E1##E2##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 1, 1> E1##E2##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 1, 2> E1##E2##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 2, 0> E1##E2##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 2, 1> E1##E2##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 2, 2> E1##E2##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 0, 0> E2##E0##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 0, 1> E2##E0##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 0, 2> E2##E0##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 1, 0> E2##E0##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 1, 1> E2##E0##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 1, 2> E2##E0##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 2, 0> E2##E0##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 2, 1> E2##E0##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 2, 2> E2##E0##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 0, 0> E2##E1##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 0, 1> E2##E1##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 0, 2> E2##E1##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 1, 0> E2##E1##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 1, 1> E2##E1##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 1, 2> E2##E1##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 2, 0> E2##E1##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 2, 1> E2##E1##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 2, 2> E2##E1##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 0, 0> E2##E2##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 0, 1> E2##E2##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 0, 2> E2##E2##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 1, 0> E2##E2##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 1, 1> E2##E2##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 1, 2> E2##E2##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 2, 0> E2##E2##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 2, 1> E2##E2##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 2, 2> E2##E2##E2##E2;                                                                     \
    };

#define STREAMLINE_SWIZZLE4_2MEMBERS(T, E0, E1, E2, E3)                                                                \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 0, 0, -1, -2> E0##E0;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 0, 1, -1, -2> E0##E1;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 0, 2, -1, -2> E0##E2;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 0, 3, -1, -2> E0##E3;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 1, 0, -1, -2> E1##E0;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 1, 1, -1, -2> E1##E1;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 1, 2, -1, -2> E1##E2;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 1, 3, -1, -2> E1##E3;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 2, 0, -1, -2> E2##E0;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 2, 1, -1, -2> E2##E1;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 2, 2, -1, -2> E2##E2;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 2, 3, -1, -2> E2##E3;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 3, 0, -1, -2> E3##E0;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 3, 1, -1, -2> E3##E1;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 3, 2, -1, -2> E3##E2;                                                                           \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 2, 3, 3, -1, -2> E3##E3;                                                                           \
    };

#define STREAMLINE_SWIZZLE4_3MEMBERS(T, E0, E1, E2, E3)                                                                \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 0, 0, 3> E0##E0##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 0, 1, 3> E0##E0##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 0, 2, 3> E0##E0##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 0, 3, 3> E0##E0##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 1, 0, 3> E0##E1##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 1, 1, 3> E0##E1##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 1, 2, 3> E0##E1##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 1, 3, 3> E0##E1##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 2, 0, 3> E0##E2##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 2, 1, 3> E0##E2##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 2, 2, 3> E0##E2##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 2, 3, 3> E0##E2##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 3, 0, 3> E0##E3##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 3, 1, 3> E0##E3##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 3, 2, 3> E0##E3##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 0, 3, 3, 3> E0##E3##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 0, 0, 3> E1##E0##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 0, 1, 3> E1##E0##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 0, 2, 3> E1##E0##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 0, 3, 3> E1##E0##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 1, 0, 3> E1##E1##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 1, 1, 3> E1##E1##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 1, 2, 3> E1##E1##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 1, 3, 3> E1##E1##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 2, 0, 3> E1##E2##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 2, 1, 3> E1##E2##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 2, 2, 3> E1##E2##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 2, 3, 3> E1##E2##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 3, 0, 3> E1##E3##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 3, 1, 3> E1##E3##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 3, 2, 3> E1##E3##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 1, 3, 3, 3> E1##E3##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 0, 0, 3> E2##E0##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 0, 1, 3> E2##E0##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 0, 2, 3> E2##E0##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 0, 3, 3> E2##E0##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 1, 0, 3> E2##E1##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 1, 1, 3> E2##E1##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 1, 2, 3> E2##E1##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 1, 2, 3> E2##E1##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 2, 0, 3> E2##E2##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 2, 1, 3> E2##E2##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 2, 2, 3> E2##E2##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 2, 3, 3> E2##E2##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 3, 0, 3> E2##E3##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 3, 1, 3> E2##E3##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 3, 2, 3> E2##E3##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 2, 3, 3, 3> E2##E3##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 0, 0, 3> E3##E0##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 0, 1, 3> E3##E0##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 0, 2, 3> E3##E0##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 0, 3, 3> E3##E0##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 1, 0, 3> E3##E1##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 1, 1, 3> E3##E1##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 1, 2, 3> E3##E1##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 1, 2, 3> E3##E1##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 2, 0, 3> E3##E2##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 2, 1, 3> E3##E2##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 2, 2, 3> E3##E2##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 2, 3, 3> E3##E2##E3;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 3, 0, 3> E3##E3##E0;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 3, 1, 3> E3##E3##E1;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 3, 2, 3> E3##E3##E2;                                                                         \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 3, 3, 3, 3, 3> E3##E3##E3;                                                                         \
    };

#define STREAMLINE_SWIZZLE4_4MEMBERS(T, E0, E1, E2, E3)                                                                \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 0> E0##E0##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 1> E0##E0##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 2> E0##E0##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 0, 3> E0##E0##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 0> E0##E0##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 1> E0##E0##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 2> E0##E0##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 1, 3> E0##E0##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 2, 0> E0##E0##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 2, 1> E0##E0##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 2, 2> E0##E0##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 2, 3> E0##E0##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 3, 0> E0##E0##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 3, 1> E0##E0##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 3, 2> E0##E0##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 0, 3, 3> E0##E0##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 0> E0##E1##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 1> E0##E1##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 2> E0##E1##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 0, 3> E0##E1##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 0> E0##E1##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 1> E0##E1##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 2> E0##E1##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 1, 3> E0##E1##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 2, 0> E0##E1##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 2, 1> E0##E1##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 2, 2> E0##E1##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 2, 3> E0##E1##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 3, 0> E0##E1##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 3, 1> E0##E1##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 3, 2> E0##E1##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 1, 3, 3> E0##E1##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 0, 0> E0##E2##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 0, 1> E0##E2##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 0, 2> E0##E2##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 0, 3> E0##E2##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 1, 0> E0##E2##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 1, 1> E0##E2##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 1, 2> E0##E2##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 1, 3> E0##E2##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 2, 0> E0##E2##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 2, 1> E0##E2##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 2, 2> E0##E2##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 2, 3> E0##E2##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 3, 0> E0##E2##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 3, 1> E0##E2##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 3, 2> E0##E2##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 2, 3, 3> E0##E2##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 0, 0> E0##E3##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 0, 1> E0##E3##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 0, 2> E0##E3##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 0, 3> E0##E3##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 1, 0> E0##E3##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 1, 1> E0##E3##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 1, 2> E0##E3##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 1, 3> E0##E3##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 2, 0> E0##E3##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 2, 1> E0##E3##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 2, 2> E0##E3##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 2, 3> E0##E3##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 3, 0> E0##E3##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 3, 1> E0##E3##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 3, 2> E0##E3##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 0, 3, 3, 3> E0##E3##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 0, 0> E1##E0##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 0, 1> E1##E0##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 0, 2> E1##E0##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 0, 3> E1##E0##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 1, 0> E1##E0##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 1, 1> E1##E0##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 1, 2> E1##E0##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 1, 3> E1##E0##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 2, 0> E1##E0##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 2, 1> E1##E0##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 2, 2> E1##E0##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 2, 3> E1##E0##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 3, 0> E1##E0##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 3, 1> E1##E0##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 3, 2> E1##E0##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 0, 3, 3> E1##E0##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 0, 0> E1##E1##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 0, 1> E1##E1##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 0, 2> E1##E1##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 0, 3> E1##E1##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 1, 0> E1##E1##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 1, 1> E1##E1##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 1, 2> E1##E1##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 1, 3> E1##E1##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 2, 0> E1##E1##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 2, 1> E1##E1##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 2, 2> E1##E1##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 2, 3> E1##E1##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 3, 0> E1##E1##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 3, 1> E1##E1##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 3, 2> E1##E1##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 1, 3, 3> E1##E1##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 0, 0> E1##E2##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 0, 1> E1##E2##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 0, 2> E1##E2##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 0, 3> E1##E2##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 1, 0> E1##E2##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 1, 1> E1##E2##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 1, 2> E1##E2##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 1, 3> E1##E2##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 2, 0> E1##E2##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 2, 1> E1##E2##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 2, 2> E1##E2##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 2, 3> E1##E2##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 3, 0> E1##E2##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 3, 1> E1##E2##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 3, 2> E1##E2##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 2, 3, 3> E1##E2##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 0, 0> E1##E3##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 0, 1> E1##E3##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 0, 2> E1##E3##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 0, 3> E1##E3##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 1, 0> E1##E3##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 1, 1> E1##E3##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 1, 2> E1##E3##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 1, 3> E1##E3##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 2, 0> E1##E3##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 2, 1> E1##E3##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 2, 2> E1##E3##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 2, 3> E1##E3##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 3, 0> E1##E3##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 3, 1> E1##E3##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 3, 2> E1##E3##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 1, 3, 3, 3> E1##E3##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 0, 0> E2##E0##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 0, 1> E2##E0##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 0, 2> E2##E0##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 0, 3> E2##E0##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 1, 0> E2##E0##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 1, 1> E2##E0##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 1, 2> E2##E0##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 1, 3> E2##E0##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 2, 0> E2##E0##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 2, 1> E2##E0##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 2, 2> E2##E0##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 2, 3> E2##E0##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 3, 0> E2##E0##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 3, 1> E2##E0##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 3, 2> E2##E0##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 0, 3, 3> E2##E0##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 0, 0> E2##E1##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 0, 1> E2##E1##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 0, 2> E2##E1##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 0, 3> E2##E1##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 1, 0> E2##E1##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 1, 1> E2##E1##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 1, 2> E2##E1##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 1, 3> E2##E1##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 2, 0> E2##E1##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 2, 1> E2##E1##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 2, 2> E2##E1##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 2, 3> E2##E1##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 3, 0> E2##E1##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 3, 1> E2##E1##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 3, 2> E2##E1##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 1, 3, 3> E2##E1##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 0, 0> E2##E2##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 0, 1> E2##E2##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 0, 2> E2##E2##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 0, 3> E2##E2##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 1, 0> E2##E2##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 1, 1> E2##E2##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 1, 2> E2##E2##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 1, 3> E2##E2##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 2, 0> E2##E2##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 2, 1> E2##E2##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 2, 2> E2##E2##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 2, 3> E2##E2##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 3, 0> E2##E2##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 3, 1> E2##E2##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 3, 2> E2##E2##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 2, 3, 3> E2##E2##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 0, 0> E2##E3##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 0, 1> E2##E3##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 0, 2> E2##E3##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 0, 3> E2##E3##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 1, 0> E2##E3##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 1, 1> E2##E3##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 1, 2> E2##E3##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 1, 3> E2##E3##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 2, 0> E2##E3##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 2, 1> E2##E3##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 2, 2> E2##E3##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 2, 3> E2##E3##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 3, 0> E2##E3##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 3, 1> E2##E3##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 3, 2> E2##E3##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 2, 3, 3, 3> E2##E3##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 0, 0> E3##E0##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 0, 1> E3##E0##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 0, 2> E3##E0##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 0, 3> E3##E0##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 1, 0> E3##E0##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 1, 1> E3##E0##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 1, 2> E3##E0##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 1, 3> E3##E0##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 2, 0> E3##E0##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 2, 1> E3##E0##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 2, 2> E3##E0##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 2, 3> E3##E0##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 3, 0> E3##E0##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 3, 1> E3##E0##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 3, 2> E3##E0##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 0, 3, 3> E3##E0##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 0, 0> E3##E1##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 0, 1> E3##E1##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 0, 2> E3##E1##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 0, 3> E3##E1##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 1, 0> E3##E1##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 1, 1> E3##E1##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 1, 2> E3##E1##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 1, 3> E3##E1##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 2, 0> E3##E1##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 2, 1> E3##E1##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 2, 2> E3##E1##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 2, 3> E3##E1##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 3, 0> E3##E1##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 3, 1> E3##E1##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 3, 2> E3##E1##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 1, 3, 3> E3##E1##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 0, 0> E3##E2##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 0, 1> E3##E2##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 0, 2> E3##E2##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 0, 3> E3##E2##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 1, 0> E3##E2##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 1, 1> E3##E2##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 1, 2> E3##E2##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 1, 3> E3##E2##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 2, 0> E3##E2##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 2, 1> E3##E2##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 2, 2> E3##E2##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 2, 3> E3##E2##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 3, 0> E3##E2##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 3, 1> E3##E2##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 3, 2> E3##E2##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 2, 3, 3> E3##E2##E3##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 0, 0> E3##E3##E0##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 0, 1> E3##E3##E0##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 0, 2> E3##E3##E0##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 0, 3> E3##E3##E0##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 1, 0> E3##E3##E1##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 1, 1> E3##E3##E1##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 1, 2> E3##E3##E1##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 1, 3> E3##E3##E1##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 2, 0> E3##E3##E2##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 2, 1> E3##E3##E2##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 2, 2> E3##E3##E2##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 2, 3> E3##E3##E2##E3;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 3, 0> E3##E3##E3##E0;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 3, 1> E3##E3##E3##E1;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 3, 2> E3##E3##E3##E2;                                                                     \
    };                                                                                                                 \
    struct                                                                                                             \
    {                                                                                                                  \
        _swizzle<T, 4, 3, 3, 3, 3> E3##E3##E3##E3;                                                                     \
    };
