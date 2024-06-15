#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace engine
{

class Transform
{
  public:
    Transform() : m_Translation(0.0f), m_Rotation(0.0f), m_Scale(1.0f)
    {
    }

    Transform(const Transform &) = default;

    const glm::vec3 &GetTranslation() const
    {
        return m_Translation;
    }

    const glm::vec3 &GetRotation() const
    {
        return m_Rotation;
    }

    const glm::vec3 &GetScale() const
    {
        return m_Scale;
    }

    void SetTranslation(const glm::vec3 &translation)
    {
        if (translation != m_Translation)
        {
            m_Translation = translation;
            m_Dirty = true;
            m_TranslationChanged = true;
        }
    }

    void SetRotation(const glm::vec3 &rotation)
    {
        if (rotation != m_Rotation)
        {
            m_Rotation = rotation;
            m_Dirty = true;
            m_RotationChanged = true;
        }
    }

    void SetScale(const glm::vec3 &scale)
    {
        if (scale != m_Scale)
        {
            m_Scale = scale;
            m_Dirty = true;
            m_ScaleChanged = true;
        }
    }

    bool IsTranslationChanged()
    {
        return m_TranslationChanged;
    }

    bool IsRotationChanged() const
    {
        return m_RotationChanged;
    }

    bool IsScaleChanged() const
    {
        return m_ScaleChanged;
    }

    bool IsDirty() const
    {
        return m_Dirty;
    }

    void SetTranslationChanged(const bool changed)
    {
        m_TranslationChanged = changed;
    }

    void SetRotationChanged(const bool changed)
    {
        m_RotationChanged = changed;
    }

    void SetScaleChanged(const bool changed)
    {
        m_ScaleChanged = changed;
    }

    void SetDirty(const bool dirty)
    {
        m_Dirty = dirty;
    }

    const glm::mat4 GetTransform() const
    {
        return glm::translate(glm::mat4(1.0f), m_Translation) * glm::toMat4(glm::quat(m_Rotation)) *
               glm::scale(glm::mat4(1.0f), m_Scale);
    }

  private:
    glm::vec3 m_Translation;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

    bool m_Dirty = true;
    bool m_TranslationChanged = true;
    bool m_RotationChanged = true;
    bool m_ScaleChanged = true;
};

}; // namespace engine