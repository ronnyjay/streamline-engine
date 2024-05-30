#pragma once

#include <entt/entt.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <string>
#include <vector>

namespace engine
{

class Identifier
{
  public:
    Identifier(const std::string &identifier) : m_Identifier(identifier)
    {
    }

    Identifier(const Identifier &) = default;

    const std::string &Get() const
    {
        return m_Identifier;
    }

    void Set(const std::string &identifier)
    {
        m_Identifier = identifier;
    }

  private:
    std::string m_Identifier;
};

class Parent
{
  public:
    Parent() : m_Parent(entt::null)
    {
    }

    Parent(const Parent &) = default;

    const entt::entity Get() const
    {
        return m_Parent;
    }

    void Set(entt::entity parent)
    {
        m_Parent = parent;
    }

  private:
    entt::entity m_Parent;
};

class Children
{
  public:
    Children() = default;
    Children(const Children &) = default;

    std::vector<entt::entity> &Get()
    {
        return m_Children;
    }

    void Emplace(entt::entity child)
    {
        m_Children.emplace_back(child);
    }

  private:
    std::vector<entt::entity> m_Children;
};

class Transform
{
  public:
    Transform() : m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f), m_Dirty(true)
    {
    }

    Transform(const Transform &) = default;

    const glm::vec3 &GetPosition() const
    {
        return m_Position;
    }

    void SetPosition(const glm::vec3 &position)
    {
        if (m_Position != position)
        {
            m_Position = position;
            m_Dirty = true;
        }
    }

    void SetPosition(const float x, const float y, const float z)
    {
        SetPosition(glm::vec3(x, y, z));
    }

    const glm::vec3 &GetRotation() const
    {
        return m_Rotation;
    }

    void SetRotation(const glm::vec3 &rotation)
    {
        if (m_Rotation != rotation)
        {
            m_Rotation = rotation;
            m_Dirty = true;
        }
    }

    void SetRotation(const float x, const float y, const float z)
    {
        SetRotation(glm::vec3(x, y, z));
    }

    const glm::vec3 &GetScale() const
    {
        return m_Scale;
    }

    void SetScale(const glm::vec3 &scale)
    {
        if (m_Scale != scale)
        {
            m_Scale = scale;
            m_Dirty = true;
        }
    }

    void SetScale(const float x, const float y, const float z)
    {
        SetScale(glm::vec3(x, y, z));
    }

    const bool IsDirty() const
    {
        return m_Dirty;
    }

    void SetDirty(const bool dirty)
    {
        m_Dirty = dirty;
    }

    const glm::mat4 GetTransform() const
    {
        return glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(glm::quat(m_Rotation)) *
               glm::scale(glm::mat4(1.0f), m_Scale);
    }

  private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

    mutable bool m_Dirty;
};

}; // namespace engine