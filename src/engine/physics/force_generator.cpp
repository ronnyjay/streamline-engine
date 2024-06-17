#include <engine/physics/force_generator.hpp>

namespace engine
{

ConstantForceGenerator::ConstantForceGenerator(const glm::vec3 &force)
    : m_Force(force)
{
}

void ConstantForceGenerator::ApplyForce(const RigidBody &body, ForceAccumulator &accumulator)
{
    accumulator.AddForce(m_Force * body.Mass);
}

} // namespace engine