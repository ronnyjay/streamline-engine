#pragma once

namespace engine
{

class Vector
{
  public:
    virtual ~Vector() = default;
};

class Vector2f : public Vector
{
  public:
    /**
     * @brief
     *
     * @param x
     * @param y
     */
    Vector2f(float x, float y)
        : x(x)
        , y(y)
    {
    }

    /**
     * @brief
     *
     * @param s
     */
    Vector2f(float s)
        : x(s)
        , y(s)
    {
    }

    /**
     * @brief
     *
     */
    Vector2f() = default;

    int x;
    int y;
};

class Vector3f : public Vector
{
  public:
    int x;
    int y;
    int z;
};

class Vector4f : public Vector
{
};

} // namespace engine