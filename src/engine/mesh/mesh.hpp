#pragma once

#include <engine/collisions/aabb.hpp>
#include <engine/debug/debug.hpp>

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <list>
#include <string>

namespace engine
{

class Mesh : public Debuggable
{
  public:
    Mesh(const std::string &identifier) : Debuggable(identifier), m_position(0.0f), m_model(1.0f)
    {
    }

    virtual void update(double);
    virtual void draw(const glm::mat4 &, const glm::mat4 &, const glm::mat4 &);
    virtual void draw_debug_info() override;

    const glm::vec3 &position() const;
    void set_position(const glm::vec3 &);

    const glm::mat4 &model() const;
    void set_model(const glm::mat4 &);

    const std::list<Mesh *> &children() const;
    void add_child(Mesh *const);

    virtual ~Mesh()
    {
    }

  protected:
    AABB m_AABB;

  private:
    glm::vec3 m_position;
    glm::mat4 m_model;
    std::list<Mesh *> m_children;
};

}; // namespace engine