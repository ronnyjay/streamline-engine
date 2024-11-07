#pragma once

#include <cmath>

namespace engine
{

template <typename T>
struct Vector2
{
    /**
     * @brief
     *
     * @param x
     * @param y
     */
    Vector2(T x, T y)
        : x(x)
        , y(y)
    {
    }

    /**
     * @brief
     *
     * @param scalar
     */
    Vector2(T &scalar)
        : x(scalar)
        , y(scalar)
    {
    }

    /**
     * @brief
     *
     */
    Vector2() = default;

    T x{};
    T y{};

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
     * @param other
     * @return Vector2<T>
     */
    Vector2<T> operator+(const Vector2<T> &other) const
    {
        return Vector2<T>(x + other.x, y + other.y);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector2<T>
     */
    Vector2<T> operator-(const Vector2<T> &other) const
    {
        return Vector2<T>(x - other.x, y - other.y);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector2<T>
     */
    Vector2<T> operator*(const Vector2<T> &other) const
    {
        return Vector2<T>(x * other.x, y * other.y);
    }

    /**
     * @brief
     *
     * @param scalar
     * @return Vector2<T>
     */
    Vector2<T> operator*(const T &scalar) const
    {
        return Vector2<T>(x * scalar, y * scalar);
    }
};

template <typename T>
struct Vector3
{
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param z
     */
    Vector3(T x, T y, T z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    /**
     * @brief
     *
     * @param scalar
     */
    Vector3(T &scalar)
        : x(scalar)
        , y(scalar)
        , z(scalar)
    {
    }

    /**
     * @brief
     *
     */
    Vector3() = default;

    T x{};
    T y{};
    T z{};

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
     * @param other
     * @return Vector2<T>
     */
    Vector3<T> operator+(const Vector3<T> &other) const
    {
        return Vector3<T>(x + other.x, y + other.y, z + other.z);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector2<T>
     */
    Vector3<T> operator-(const Vector3<T> &other) const
    {
        return Vector3<T>(x - other.x, y - other.y, z - other.z);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector2<T>
     */
    Vector3<T> operator*(const Vector3<T> &other) const
    {
        return Vector3<T>(x * other.x, y * other.y, z * other.z);
    }

    /**
     * @brief
     *
     * @param scalar
     * @return Vector3<T>
     */
    Vector3<T> operator*(const T &scalar) const
    {
        return Vector3<T>(x * scalar, y * scalar, z * scalar);
    }
};

template <typename T>
struct Vector4
{
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param z
     * @param w
     */
    Vector4(T x, T y, T z, T w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    /**
     * @brief
     *
     * @param scalar
     */
    Vector4(T scalar)
        : x(scalar)
        , y(scalar)
        , z(scalar)
        , w(scalar)
    {
    }

    /**
     * @brief
     *
     */
    Vector4() = default;

    T x{};
    T y{};
    T z{};
    T w{};

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
     * @param other
     * @return Vector2<T>
     */
    Vector4<T> operator+(const Vector4<T> &other) const
    {
        return Vector4<T>(x + other.x, y + other.y, z + other.z, w * other.w);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector2<T>
     */
    Vector4<T> operator-(const Vector4<T> &other) const
    {
        return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector2<T>
     */
    Vector4<T> operator*(const Vector4<T> &other) const
    {
        return Vector4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    /**
     * @brief
     *
     * @param scalar
     * @return Vector4<T>
     */
    Vector4<T> operator*(const T &scalar) const
    {
        return Vector4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
    }
};

typedef Vector2<int>    Vector2i;
typedef Vector2<float>  Vector2f;
typedef Vector2<double> Vector2d;

typedef Vector3<int>    Vector3i;
typedef Vector3<float>  Vector3f;
typedef Vector3<double> Vector3d;

typedef Vector4<int>    Vector4i;
typedef Vector4<float>  Vector4f;
typedef Vector4<double> Vector4d;

} // namespace engine