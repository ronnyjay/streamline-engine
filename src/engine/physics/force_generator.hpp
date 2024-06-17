#pragma once

#include <engine/physics/force_accumulator.hpp>
#include <engine/physics/rigid_body.hpp>

#include <glm/glm.hpp>

namespace engine
{

class Entity;

class ForceGenerator
{
  public:
    ForceGenerator() = default;

    virtual void ApplyForce(const RigidBody &, ForceAccumulator &) = 0;
};

class ConstantForceGenerator : public ForceGenerator
{
  public:
    ConstantForceGenerator(const glm::vec3 &);

    virtual void ApplyForce(const RigidBody &, ForceAccumulator &) override;

  private:
    glm::vec3 m_Force;
};

} // namespace engine