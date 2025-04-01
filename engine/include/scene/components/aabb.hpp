#pragma once

#include "renderer/model.hpp"

namespace engine
{

/// TODO: Decouple data from OpenGL?
/// TODO: Remove vertex data?
/// TODO: Remove rotation, scale?
struct AABB
{
    AABB(const std::shared_ptr<Model> &model);

    AABB(AABB const &other)  = delete;
    AABB(AABB &other)        = delete;
    AABB(AABB const &&other) = delete;
    AABB(AABB &&other);

    ~AABB();

    // clang-format off
    void translate(const vec3 &translation);
    void rotate(const vec3 &transform);
    void scale(const vec3 &scale);

    void draw();
    // clang-format on

    const vec3 &min() const;
    const vec3 &max() const;

    const vec3 &center() const;
    const vec3 &halfExtents() const;

  private:
    vec3 m_globalMin;
    vec3 m_globalMax;

    vec3 m_localMin;
    vec3 m_localMax;

    vec3 m_center;
    vec3 m_halfExtents;

    vec3 m_lastScale;
    vec3 m_lastRotation;

  private:
    unsigned int      m_VAO;
    unsigned int      m_VBO;
    unsigned int      m_EBO;

    std::vector<vec3> m_vertexData;

    void              updateVertices();
};

} // namespace engine