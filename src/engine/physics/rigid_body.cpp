#include <engine/physics/rigid_body.hpp>

namespace engine
{

RigidBody::RigidBody()
    : Mass(1.0f)
    , Restituion(0.0f)
    , RestitutionThreshold(0.5f)
    , Velocity(0.0f)
    , AngularVelocity(0.0f)
{
}

} // namespace engine