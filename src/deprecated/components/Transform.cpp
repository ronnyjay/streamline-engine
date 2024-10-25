#include <engine/Components/Transform.hpp>

using namespace engine;

Transform::Transform()
    : m_Position(0.0f)
    , m_Rotation(0.0f)
    , m_Scale(1.0f)
    , m_Dirty(false)
    , m_PositionChanged(false)
    , m_RotationChanged(false)
    , m_ScaleChanged(false)
{
}

const glm::vec3 &Transform::GetPosition() const
{
    return m_Position;
}

const glm::vec3 &Transform::GetRotation() const
{
    return m_Rotation;
}

const glm::vec3 &Transform::GetScale() const
{
    return m_Scale;
}

void Transform::SetPosition(const glm::vec3 &translation)
{
    if (translation != m_Position)
    {
        m_Position = translation;
        m_Dirty = true;
        m_PositionChanged = true;
    }
}

void Transform::SetRotation(const glm::vec3 &rotation)
{
    if (rotation != m_Rotation)
    {
        m_Rotation = rotation;
        m_Dirty = true;
        m_RotationChanged = true;
    }
}

void Transform::SetScale(const glm::vec3 &scale)
{
    if (scale != m_Scale)
    {
        m_Scale = scale;
        m_Dirty = true;
        m_ScaleChanged = true;
    }
}

bool Transform::IsPositionChanged() const
{
    return m_PositionChanged;
}

bool Transform::IsRotationChanged() const
{
    return m_RotationChanged;
}

bool Transform::IsScaleChanged() const
{
    return m_ScaleChanged;
}

bool Transform::IsDirty() const
{
    return m_Dirty;
}

void Transform::SetTranslationChanged(const bool changed)
{
    m_PositionChanged = changed;
}

void Transform::SetRotationChanged(const bool changed)
{
    m_RotationChanged = changed;
}

void Transform::SetScaleChanged(const bool changed)
{
    m_ScaleChanged = changed;
}

void Transform::SetDirty(const bool dirty)
{
    m_Dirty = dirty;
}

const glm::mat4 Transform::GetTransform() const
{
    return glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(glm::quat(m_Rotation)) *
           glm::scale(glm::mat4(1.0f), m_Scale);
}
