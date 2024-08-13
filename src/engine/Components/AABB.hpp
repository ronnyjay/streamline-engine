#pragma once

#include <engine/Components/Model.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace engine
{

class AABB
{
  public:
    AABB(std::shared_ptr<Model>);
    AABB(AABB &&);

    const glm::vec3 &Min() const;
    const glm::vec3 &Max() const;

    const glm::vec3 &Center() const;
    const glm::vec3 &HalfDimensions() const;

    void Update(const std::vector<glm::vec3> &);
    void Translate(const glm::vec3 &);

    void Draw();

    ~AABB();

  private:
    glm::vec3 m_GlobalMin;
    glm::vec3 m_GlobalMax;

    glm::vec3 m_LocalMin;
    glm::vec3 m_LocalMax;

    glm::vec3 m_Center;
    glm::vec3 m_HalfDimensions;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

    void UpdateVertices();
};

} // namespace engine