#pragma once

#include <engine/Components/Model.hpp>

namespace engine
{

class BSphere
{
  public:
    BSphere(std::shared_ptr<Model>);

    BSphere(BSphere &&);

    float Radius() const;

    const glm::vec3 &Center() const;
    const glm::vec3 &Translation() const;

    void Update(const std::vector<glm::vec3> &);
    void Translate(const glm::vec3 &);

    bool Intersects(const BSphere &);

    void Draw();

    ~BSphere();

  private:
    float m_Radius;

    glm::vec3 m_Center;
    glm::vec3 m_Translation;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

    void UpdateVertices();

    static constexpr float RINGS = 32.0f;
    static constexpr float SEGMENTS = 64.0f;
};

} // namespace engine
