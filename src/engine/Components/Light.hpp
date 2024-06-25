#pragma once

#include <glm/glm.hpp>

namespace engine
{

class Light
{
  public:
    Light()
        : m_Color(1.0f)
    {
    }

    Light(const glm::vec4 &color)
        : m_Color(color)
    {
    }

    Light(const Light &) = default;

    const glm::vec4 &GetColor() const
    {
        return m_Color;
    }

    void SetColor(const glm::vec4 &color)
    {
        m_Color = color;
    }

  private:
    glm::vec4 m_Color;
};

class ShaderLight
{
  public:
    ShaderLight()
        : m_Position(0.0f)
    {
    }

    ShaderLight(const glm::vec4 &position)
        : m_Position(position)
    {
    }

    ShaderLight(const ShaderLight &) = default;

    const glm::vec4 &GetPosition() const
    {
        return m_Position;
    }

    const Light &GetProperties() const
    {
        return m_Properties;
    }

    void SetPosition(const glm::vec4 &position)
    {
        m_Position = position;
    }

    void SetProperties(const Light &properties)
    {
        m_Properties = properties;
    }

  private:
    glm::vec4 m_Position;
    Light m_Properties;
};

}; // namespace engine