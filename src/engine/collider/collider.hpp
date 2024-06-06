#pragma once

#include <engine/mesh/mesh.hpp>
#include <engine/model/model.hpp>

#include <glm/glm.hpp>

#include <limits>
#include <vector>

namespace engine
{

class AABB
{
  public:
    AABB(const glm::vec3 &min = glm::vec3(FLT_MAX), const glm::vec3 &max = glm::vec3(-FLT_MAX));

    void Translate(const glm::vec3 &);
    void Update(const std::vector<glm::vec3> &);
    void Draw();

    bool Intersects(const AABB &);

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