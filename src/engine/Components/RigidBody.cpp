#include <engine/Components/RigidBody.hpp>

namespace engine
{

RigidBody::RigidBody()
    : m_InverseMass(1.0f)
    , m_Elasticity(0.8f)
    , m_Friction(0.8f)
    , m_LinearVelocity(0.0f)
    , m_Force(0.0f)
    , m_AngularVelocity(0.0f)
    , m_Torque(0.0f)
    , m_InverseInertia(0.0f)
    , m_InverseInertiaTensor(1.0f)

{
}

float RigidBody::GetInverseMass() const
{
    return m_InverseMass;
}

float RigidBody::GetElasticity() const
{
    return m_Elasticity;
}

float RigidBody::GetFriction() const
{
    return m_Friction;
}

const glm::vec3 &RigidBody::GetLinearVelocity() const
{
    return m_LinearVelocity;
}

const glm::vec3 &RigidBody::GetForce() const
{
    return m_Force;
}

const glm::vec3 &RigidBody::GetAngularVelocity() const
{
    return m_AngularVelocity;
}

const glm::vec3 &RigidBody::GetTorque() const
{
    return m_Torque;
}

const glm::mat3 &RigidBody::GetInertiaTensor() const
{
    return m_InverseInertiaTensor;
}

void RigidBody::SetInverseMass(const float inverseMass)
{
    m_InverseMass = inverseMass;
}

void RigidBody::SetElasticity(const float elasticity)
{
    m_Elasticity = elasticity;
}

void RigidBody::SetFriction(const float friction)
{
    m_Friction = friction;
}

void RigidBody::SetLinearVelocity(const glm::vec3 &linearVelocity)
{
    m_LinearVelocity = linearVelocity;
}

void RigidBody::SetAngularVelocity(const glm::vec3 &angularVelocity)
{
    m_AngularVelocity = angularVelocity;
}

void RigidBody::ApplyLinearImpulse(const glm::vec3 &force)
{
    m_LinearVelocity += force * m_InverseMass;
}

void RigidBody::ApplyAngularImpulse(const glm::vec3 &force)
{
    m_AngularVelocity += m_InverseInertiaTensor * force;
}

void RigidBody::AddForce(const glm::vec3 &addedForce)
{
    m_Force += addedForce;
}

void RigidBody::AddTorque(const glm::vec3 &addedTorque)
{
    m_Torque += addedTorque;
}

void RigidBody::ClearForces()
{
    m_Force = glm::vec3(0.0f);
    m_Torque = glm::vec3(0.0f);
}

} // namespace engine