#pragma once

#include "engine/texture/texture.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace engine
{

struct MaterialAttributes
{
    MaterialAttributes() : m_Ns(0.0f), m_Ka(0.0f), m_Kd(0.0f), m_Ks(0.0f), m_Ke(0.0f), m_Ni(0.0f), m_d(0.0f), m_illum(0), m_texture(nullptr)
    {
    }

    float m_Ns;           // Specular exponent
                          //
    glm::vec3 m_Ka;       // Ambient color
    glm::vec3 m_Kd;       // Diffuse color
    glm::vec3 m_Ks;       // Specular color
    glm::vec3 m_Ke;       // Emissive color
                          //
    float m_Ni;           // Index of refraction
    float m_d;            // dissolve / transparency
                          //
    unsigned int m_illum; // illumination

    std::unique_ptr<Texture> m_texture;
};

class Material
{
  public:
    Material()
    {
    }

    bool load_material(const std::basic_string<char> &mtl_path);

    std::unordered_map<std::basic_string<char>, MaterialAttributes> m_materials;
};

}; // namespace engine