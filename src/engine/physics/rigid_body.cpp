#include <engine/physics/rigid_body.hpp>

namespace engine
{

RigidBody::RigidBody()
    : Mass(1.0f)
    , Restitution(0.1f)
    , RestitutionThreshold(0.5f)
    , Velocity(0.0f)
    , Impulse(0.0f)
{
}

} // namespace engine