#pragma once

#include <engine/debug/debug.hpp>

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <list>
#include <string>

namespace engine
{

typedef enum
{
    X,
    Y,
} RotationAxis;

class Mesh : public Debuggable
{
  public:
    Mesh(const std::string &identifier)
        : Debuggable(identifier), m_position(0.0f), m_rotation_angle(0.0f), m_rotation_speed(0.0f), m_rotation_axis(X), m_model(1.0f)
    {
    }

    virtual void update(double);
    virtual void draw(const glm::mat4 &, const glm::mat4 &, const glm::mat4 &);
    virtual void draw_debug_info() override;

    const glm::vec3 &position() const;
    void set_position(const glm::vec3 &);

    const float rotation_angle() const;
    void set_rotation_angle(const float);

    const float rotation_speed() const;
    void set_rotation_speed(const float);

    const glm::vec3 rotation_axis() const;
    void set_rotation_axis(const RotationAxis);

    const glm::mat4 &model() const;
    void set_model(const glm::mat4 &);

    const std::list<Mesh *> &children() const;
    void add_child(Mesh *const);

    virtual ~Mesh()
    {
    }

  private:
    glm::vec3 m_position;

    float m_rotation_angle;
    float m_rotation_speed;
    RotationAxis m_rotation_axis;

    glm::mat4 m_model;

    std::list<Mesh *> m_children;
};

}; // namespace engine