#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace engine
{

struct TransformVector
{
    TransformVector(const float scalar)
        : Vector(scalar)
    {
    }

    TransformVector &operator=(const glm::vec3 &v)
    {
        if (Vector != v)
        {
            Vector = v;
            Changed = true;
        }

        return *this;
    }

    operator glm::vec3() const
    {
        return Vector;
    }

    bool Changed = false;

  private:
    glm::vec3 Vector = glm::vec3(0.0f);
};

class Transform
{
  public:
    Transform()
        : Position(0.0f)
        , Rotation(0.0f)
        , Scale(1.0f)
    {
    }

    Transform(const Transform &) = default;

    const glm::mat4 GetTransform() const
    {
        return glm::translate(glm::mat4(1.0f), (glm::vec3)Position) * glm::toMat4(glm::quat((glm::vec3)Rotation)) *
               glm::scale(glm::mat4(1.0f), glm::vec3(Scale));
    }

    bool Dirty() const
    {
        return Position.Changed || Rotation.Changed || Scale.Changed;
    }

    TransformVector Position;
    TransformVector Rotation;
    TransformVector Scale;

  private:
};

}; // namespace engine