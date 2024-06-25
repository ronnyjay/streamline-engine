#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace engine
{

class Transform
{
  public:
    Transform();
    Transform(const Transform &) = default;

    const glm::vec3 &GetPosition() const;
    const glm::vec3 &GetRotation() const;
    const glm::vec3 &GetScale() const;

    void SetPosition(const glm::vec3 &translation);
    void SetRotation(const glm::vec3 &rotation);
    void SetScale(const glm::vec3 &scale);

    bool IsPositionChanged() const;
    bool IsRotationChanged() const;
    bool IsScaleChanged() const;
    bool IsDirty() const;

    void SetTranslationChanged(const bool changed);
    void SetRotationChanged(const bool changed);
    void SetScaleChanged(const bool changed);
    void SetDirty(const bool dirty);

    const glm::mat4 GetTransform() const;

  private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

    bool m_Dirty;
    bool m_PositionChanged;
    bool m_RotationChanged;
    bool m_ScaleChanged;
};

}; // namespace engine