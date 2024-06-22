#pragma once

#include <engine/mesh/mesh.hpp>
#include <engine/model/model.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace engine
{

struct Collision
{
    glm::vec3 Depth;
    glm::vec3 Normal;
    bool Collided = false;
};

class AABB
{
  public:
    AABB(std::shared_ptr<Model>);

    void Translate(const glm::vec3 &);
    void Update(const std::vector<glm::vec3> &);
    void Draw();

    bool Intersects(const AABB &);
    // Collision Intersects(const AABB &);

    glm::vec3 const &Min() const
    {
        return m_Min;
    }

    glm::vec3 const &Max() const
    {
        return m_Max;
    }

    bool GetColliding() const;
    void SetColliding(const bool);

    ~AABB();

  private:
    glm::vec3 m_Min;
    glm::vec3 m_Max;

    // Used as reference for applying translations as to not compound
    glm::vec3 m_RefMin;
    glm::vec3 m_RefMax;

    bool m_Colliding;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

    void UpdateVertices();
};

}; // namespace engine