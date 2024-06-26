#pragma once

#include <glm/glm.hpp>

namespace engine
{

class RigidBody
{
  public:
    RigidBody();
    RigidBody(const RigidBody &) = default;

    float GetInverseMass() const;
    float GetElasticity() const;
    float GetFriction() const;

    const glm::vec3 &GetLinearVelocity() const;
    const glm::vec3 &GetForce() const;

    const glm::vec3 &GetAngularVelocity() const;
    const glm::vec3 &GetTorque() const;

    const glm::mat3 &GetInertiaTensor() const;

    void SetInverseMass(const float);
    void SetElasticity(const float);
    void SetFriction(const float);

    void SetLinearVelocity(const glm::vec3 &);
    void SetAngularVelocity(const glm::vec3 &);

    void ApplyLinearImpulse(const glm::vec3 &);
    void ApplyAngularImpulse(const glm::vec3 &);

    void AddForce(const glm::vec3 &);
    void AddTorque(const glm::vec3 &);

    void ClearForces();

    void UpdateInertiaTensor();

  private:
    float m_InverseMass;
    float m_Elasticity;
    float m_Friction;

    glm::vec3 m_LinearVelocity;
    glm::vec3 m_Force;

    glm::vec3 m_AngularVelocity;
    glm::vec3 m_Torque;
    glm::vec3 m_InverseInertia;

    glm::mat3 m_InverseInertiaTensor;
};

} // namespace engine