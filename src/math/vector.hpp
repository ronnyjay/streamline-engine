#pragma once

#include <cmath>
#include <stdexcept>

namespace engine
{

template <std::size_t N, typename T>
class Vector
{
  public:
    /**
     * @brief
     *
     * @param index
     * @return T&
     */
    T &operator[](std::size_t index)
    {
        if (index >= N)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    /**
     * @brief
     *
     * @param index
     * @return const T&
     */
    const T &operator[](std::size_t index) const
    {
        if (index >= N)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

  private:
    std::array<T, N> data;
};

template <typename T>
struct Vector<2, T>
{
    T x{};
    T y{};

    /**
     * @brief
     *
     * @param x
     * @param y
     */
    Vector(T x, T y)
        : x(x)
        , y(y)
    {
    }

    /**
     * @brief
     *
     * @param s
     */
    Vector(T s)
        : x(s)
        , y(s)
    {
    }

    /**
     * @brief
     *
     */
    Vector() = default;

    /**
     * @brief
     *
     * @return float
     */
    float Length() const
    {
        float x2 = static_cast<float>(x * x);
        float y2 = static_cast<float>(y * y);

        return std::sqrt(x2 + y2);
    }

    /**
     * @brief
     *
     * @param index
     * @return T&
     */
    T &operator[](std::size_t index)
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        throw std::out_of_range("Index out of range");
    }

    /**
     * @brief
     *
     * @param index
     * @return const T&
     */
    const T &operator[](std::size_t index) const
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        throw std::out_of_range("Index out of range");
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector<2, T>
     */
    Vector<2, T> operator+(const Vector<2, T> &other) const
    {
        return Vector<2, T>(x + other.x, y + other.y);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector<2, T>
     */
    Vector<2, T> operator-(const Vector<2, T> &other) const
    {
        return Vector<2, T>(x - other.x, y - other.y);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector<2, T>
     */
    Vector<2, T> operator*(const Vector<2, T> &other) const
    {
        return Vector<2, T>(x * other.x, y * other.y);
    }

    /**
     * @brief
     *
     * @param s
     * @return Vector<2, T>
     */
    Vector<2, T> operator*(T s) const
    {
        return Vector<2, T>(x * s, y * s);
    }
};

template <typename T>
struct Vector<3, T>
{
    T x{};
    T y{};
    T z{};

    /**
     * @brief
     *
     * @param x
     * @param y
     */
    Vector(T x, T y, T z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    /**
     * @brief
     *
     * @param s
     */
    Vector(T s)
        : x(s)
        , y(s)
        , z(s)
    {
    }

    /**
     * @brief
     *
     */
    Vector() = default;

    /**
     * @brief
     *
     * @return float
     */
    float Length() const
    {
        float x2 = static_cast<float>(x * x);
        float y2 = static_cast<float>(y * y);
        float z2 = static_cast<float>(z * z);

        return std::sqrt(x2 + y2 + z2);
    }

    /**
     * @brief
     *
     * @param index
     * @return T&
     */
    T &operator[](std::size_t index)
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        if (index == 2)
            return z;
        throw std::out_of_range("Index out of range");
    }

    /**
     * @brief
     *
     * @param index
     * @return const T&
     */
    const T &operator[](std::size_t index) const
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        if (index == 2)
            return z;
        throw std::out_of_range("Index out of range");
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector<3, T>
     */
    Vector<3, T> operator+(const Vector<3, T> &other) const
    {
        return Vector<3, T>(x + other.x, y + other.y, z + other.z);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector<3, T>
     */
    Vector<3, T> operator-(const Vector<3, T> &other) const
    {
        return Vector<3, T>(x - other.x, y - other.y, z - other.z);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector<3, T>
     */
    Vector<3, T> operator*(const Vector<3, T> &other) const
    {
        return Vector<3, T>(x * other.x, y * other.y, z * other.z);
    }

    /**
     * @brief
     *
     * @param s
     * @return Vector<3, T>
     */
    Vector<3, T> operator*(T s) const
    {
        return Vector<3, T>(x * s, y * s, z * s);
    }
};

template <typename T>
struct Vector<4, T>
{
    T x{};
    T y{};
    T z{};
    T w{};

    /**
     * @brief
     *
     * @param x
     * @param y
     */
    Vector(T x, T y, T z, T w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    /**
     * @brief
     *
     * @param s
     */
    Vector(T s)
        : x(s)
        , y(s)
        , z(s)
        , w(s)
    {
    }

    /**
     * @brief
     *
     */
    Vector() = default;

    /**
     * @brief
     *
     * @return float
     */
    float Length() const
    {
        float x2 = static_cast<float>(x * x);
        float y2 = static_cast<float>(y * y);
        float z2 = static_cast<float>(z * z);
        float w2 = static_cast<float>(w * w);

        return std::sqrt(x2 + y2 + z2 + w2);
    }

    /**
     * @brief
     *
     * @param index
     * @return T&
     */
    T &operator[](std::size_t index)
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        if (index == 2)
            return z;
        if (index == 3)
            return w;
        throw std::out_of_range("Index out of range");
    }

    /**
     * @brief
     *
     * @param index
     * @return const T&
     */
    const T &operator[](std::size_t index) const
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        if (index == 2)
            return z;
        if (index == 3)
            return w;
        throw std::out_of_range("Index out of range");
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector<4, T>
     */
    Vector<4, T> operator+(const Vector<4, T> &other) const
    {
        return Vector<4, T>(x + other.x, y + other.y, z + other.z, w * other.w);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector<4, T>
     */
    Vector<4, T> operator-(const Vector<4, T> &other) const
    {
        return Vector<4, T>(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector<4, T>
     */
    Vector<4, T> operator*(const Vector<4, T> &other) const
    {
        return Vector<4, T>(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    /**
     * @brief
     *
     * @param s
     * @return Vector<4, T>
     */
    Vector<4, T> operator*(T s) const
    {
        return Vector<4, T>(x * s, y * s, z * s, w * s);
    }
};

template <typename T>
float Dot(const Vector<2, T> &a, const Vector<2, T> &b)
{
    return static_cast<float>((a.x * b.x) + (a.y * b.y));
}

/**
 * @brief
 *
 * @tparam T
 * @param a
 * @param b
 * @return float
 */
template <typename T>
float Dot(const Vector<3, T> &a, const Vector<3, T> &b)
{
    return static_cast<float>((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

/**
 * @brief
 *
 * @tparam T
 * @param a
 * @param b
 * @return float
 */
template <typename T>
float Dot(const Vector<4, T> &a, const Vector<4, T> &b)
{
    return static_cast<float>((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

/**
 * @brief
 *
 * @tparam T
 * @param a
 * @param b
 * @return Vector3<T>
 */
template <typename T>
Vector<3, T> Cross(const Vector<3, T> &a, const Vector<3, T> &b)
{
    T x = (a.y * b.z) - (a.z * b.y);
    T y = (a.z * b.x) - (a.x * b.z);
    T z = (a.x * b.y) - (a.y * b.x);

    return Vector3<T>(x, y, z);
}

typedef Vector<2, int>    Vector2i;
typedef Vector<2, float>  Vector2f;
typedef Vector<2, double> Vector2d;

typedef Vector<3, int>    Vector3i;
typedef Vector<3, float>  Vector3f;
typedef Vector<3, double> Vector3d;

typedef Vector<4, int>    Vector4i;
typedef Vector<4, float>  Vector4f;
typedef Vector<4, double> Vector4d;

} // namespace engine