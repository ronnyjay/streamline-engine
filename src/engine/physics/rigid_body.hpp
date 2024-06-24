#pragma once

#include <glm/glm.hpp>

namespace engine
{

class RigidBody
{
  public:
    RigidBody();
    RigidBody(const RigidBody &) = default;

    float GetMass() const;
    float GetInverseMass() const;

    float GetRestitution() const;

    glm::vec3 const &GetLinearVelocity() const;
    glm::vec3 const &GetAngularVelocity() const;

    glm::mat3 const &GetInertiaTensor() const;

    void SetMass(const float);
    void SetRestitution(const float);

    void SetLinearVelocity(const glm::vec3 &);
    void SetAngularVelocity(const glm::vec3 &);

    void ApplyLinearImpulse(const glm::vec3 &);
    void ApplyAngularImpulse(const glm::vec3 &);

  private:
    float m_Mass;
    float m_Restitution;

    glm::vec3 m_Torque;
    glm::vec3 m_LinearVelocity;
    glm::vec3 m_AngularVelocity;

    mutable glm::mat3 m_InertiaTensor;
};

} // namespace engine