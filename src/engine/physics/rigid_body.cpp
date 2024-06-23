#include <engine/physics/rigid_body.hpp>

namespace engine
{

RigidBody::RigidBody()
    : m_Mass(1.0f)
    , m_Restitution(0.1f)
    , m_LinearVelocity(0.0f)
    , m_AngularVelocity(0.0f)
{
}

float RigidBody::GetMass() const
{
    return m_Mass;
}

float RigidBody::GetInverseMass() const
{
    return 1 / m_Mass;
}

float RigidBody::GetRestitution() const
{
    return m_Restitution;
}

glm::vec3 const &RigidBody::GetLinearVelocity() const
{
    return m_LinearVelocity;
}

glm::vec3 const &RigidBody::GetAngularVelocity() const
{
    return m_AngularVelocity;
}

void RigidBody::SetMass(const float mass)
{
    m_Mass = mass;
}

void RigidBody::SetRestitution(const float restitution)
{
    m_Restitution = restitution;
}

void RigidBody::SetLinearVelocity(const glm::vec3 &velocity)
{
    m_LinearVelocity = velocity;
}

void RigidBody::SetAngularVelocity(const glm::vec3 &velocity)
{
    m_AngularVelocity = velocity;
}

void RigidBody::ApplyLinearImpulse(const glm::vec3 &force)
{
    m_LinearVelocity += force * GetInverseMass();
}

void RigidBody::ApplyAngularImpulse(const glm::vec3 &force)
{
    /** TODO: Implement */
}

} // namespace engine