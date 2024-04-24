#pragma once

#include <engine/mesh/mesh.hpp>

#include <glm/ext/vector_float3.hpp>
#include <string>
#include <vector>

namespace engine
{

namespace mesh
{
typedef glm::vec3 vertex;
typedef glm::vec2 uv;
typedef glm::vec3 normal;
typedef unsigned int index;

class point_indices
{
  public:
    bool operator==(const point_indices &other) const
    {
        return std::tie(vertex_index, uv_index, normal_index) == std::tie(other.vertex_index, other.uv_index, other.normal_index);
    }

    index vertex_index;
    index uv_index;
    index normal_index;
};

struct point_indices_hash {
    std::size_t operator()(const point_indices& key) const {
        // Combine hashes of individual integers
        return std::hash<int>()(key.vertex_index) ^ std::hash<int>()(key.uv_index) ^ std::hash<int>()(key.normal_index);
    }
};

struct face_indices
{
    point_indices v0;
    point_indices v1;
    point_indices v2;
};

// typedef std::array<face_index, 9> face_indices;
typedef std::array<float, 8> point;

class obj : public mesh_t
{
  public:
    obj(const std::basic_string<char> &name, const std::basic_string<char> &obj_path);

    virtual void update(double) override;
    void draw(const glm::mat4 &, const glm::mat4 &, const glm::mat4 &) override;

  private:
    std::vector<index> m_indices; // index into m_data to find vertex - EBO
    std::vector<point> m_points;  // vertex, uv, normal - VBO
};

}; // namespace mesh

}; // namespace engine