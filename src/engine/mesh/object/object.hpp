#pragma once

#include <engine/collisions/AABB.hpp>
#include <engine/mesh/mesh.hpp>
#include <engine/mesh/object/material/material.hpp>
#include <engine/renderer/EBO/EBO.hpp>
#include <engine/renderer/VAO/VAO.hpp>
#include <engine/renderer/VBO/VBO.hpp>
#include <engine/shader/shader.hpp>
#include <engine/texture/texture.hpp>

#include <glm/ext/vector_float3.hpp>

#include <string>
#include <vector>

namespace engine
{

typedef glm::vec3 Vertex;
typedef glm::vec2 Uv;
typedef glm::vec3 Normal;
typedef unsigned int Index;

class PointIndices
{
  public:
    bool operator==(const PointIndices &other) const
    {
        return std::tie(vertex_index, uv_index, normal_index) == std::tie(other.vertex_index, other.uv_index, other.normal_index);
    }

    Index vertex_index;
    Index uv_index;
    Index normal_index;
};

struct PointIndicesHash
{
    std::size_t operator()(const PointIndices &key) const
    {
        // Combine hashes of individual integers
        return std::hash<int>()(key.vertex_index) ^ std::hash<int>()(key.uv_index) ^ std::hash<int>()(key.normal_index);
    }
};

struct FaceIndices
{
    PointIndices v0;
    PointIndices v1;
    PointIndices v2;
};

typedef std::array<float, 8> Point;

class Object : public Mesh
{
  public:
    Object(const std::basic_string<char> &name, const std::basic_string<char> &obj_path);

    virtual void update(double) override;
    virtual void draw(const glm::mat4 &, const glm::mat4 &, const glm::mat4 &) override;

    void check_collision(const glm::vec3 &);

  private:
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;

    AABB m_AABB;

    Material m_material;

    ShaderProgram m_shader_program;
    ShaderProgram m_texture_shader_program;

    std::vector<Index> m_indices; // index into m_data to find vertex - EBO
    std::vector<Point> m_points;  // vertex, uv, normal - VBO
};

}; // namespace engine