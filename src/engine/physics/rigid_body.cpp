#include <engine/physics/rigid_body.hpp>
#include <glm/ext/quaternion_common.hpp>
#include <glm/fwd.hpp>

namespace engine
{

RigidBody::RigidBody()
    : m_Mass(1.0f)
    , m_Restitution(0.1f)
    , m_Torque(0.0f)
    , m_LinearVelocity(0.0f)
    , m_AngularVelocity(0.0f)
    , m_InertiaTensor(0.0f)
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

glm::mat3 const &RigidBody::GetInertiaTensor() const
{
    float w2 = 2.0f * 2.0f;
    float h2 = 2.0f * 2.0f;
    float d2 = 2.0f * 2.0f;

    float Ixx = (1.0f / 12.0f) * m_Mass * (h2 + d2);
    float Iyy = (1.0f / 12.0f) * m_Mass * (w2 + d2);
    float Izz = (1.0f / 12.0f) * m_Mass * (w2 + h2);

    m_InertiaTensor[0][0] = Ixx;
    m_InertiaTensor[1][1] = Iyy;
    m_InertiaTensor[2][2] = Izz;

    // float width = 4.0f;  // Width of the pyramid base
    // float height = 4.0f; // Height of the pyramid
    // float depth = 4.0f;  // Depth of the pyramid base

    // float w2 = width * width;
    // float h2 = height * height;
    // float d2 = depth * depth;

    // float Ixx = (1.0f / 20.0f) * m_Mass * (h2 + (w2 / 4.0f));
    // float Iyy = (1.0f / 20.0f) * m_Mass * (h2 + (d2 / 4.0f));
    // float Izz = (1.0f / 10.0f) * m_Mass * ((w2 / 4.0f) + (d2 / 4.0f));

    // m_InertiaTensor[0][0] = Ixx;
    // m_InertiaTensor[1][1] = Iyy;
    // m_InertiaTensor[2][2] = Izz;

    return m_InertiaTensor;
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
    m_AngularVelocity += glm::inverse(GetInertiaTensor()) * force;
}

} // namespace engine