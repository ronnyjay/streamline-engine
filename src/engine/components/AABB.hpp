#pragma once

#include <engine/mesh/mesh.hpp>
#include <engine/model/model.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace engine
{

class AABB
{
  public:
    AABB(std::shared_ptr<Model>);

    void Translate(const glm::vec3 &);
    void Update(const std::vector<glm::vec3> &);
    void Draw();

    bool Intersects(const AABB &);

    bool GetColliding() const;
    void SetColliding(const bool);

    ~AABB();

  private:
    glm::vec3 m_GlobalMin;
    glm::vec3 m_LocalMin;
    glm::vec3 m_GlobalMax;
    glm::vec3 m_LocalMax;

    bool m_Colliding;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

    void UpdateVertices();
};

}; // namespace engine