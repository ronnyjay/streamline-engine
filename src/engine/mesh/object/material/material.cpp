#include "material.hpp"
#include "engine/texture/texture.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace engine;

bool Material::load_material(const std::basic_string<char> &mtl_path)
{
    std::ifstream mtl_file(mtl_path);
    std::string line;

    MaterialAttributes ma;
    std::string material_attribute_name;

    if (!mtl_file.is_open())
    {
        return false;
    }

    while (std::getline(mtl_file, line))
    {
        std::stringstream ss(line);
        std::string token;
        ss >> token;

        if (token == "newmtl")
        {
            if (material_attribute_name.length() > 0)
                m_materials[material_attribute_name] = std::move(ma);

            material_attribute_name.clear();
            ss >> material_attribute_name;
        }
        else if (token == "Ns")
        {
            ss >> ma.m_Ns;
        }
        else if (token == "Ka")
        {
            ss >> ma.m_Ka.x;
            ss >> ma.m_Ka.y;
            ss >> ma.m_Ka.z;
        }
        else if (token == "Kd")
        {
            ss >> ma.m_Kd.x;
            ss >> ma.m_Kd.y;
            ss >> ma.m_Kd.z;
        }
        else if (token == "Ks")
        {
            ss >> ma.m_Ks.x;
            ss >> ma.m_Ks.y;
            ss >> ma.m_Ks.z;
        }
        else if (token == "Ke")
        {
            ss >> ma.m_Ke.x;
            ss >> ma.m_Ke.y;
            ss >> ma.m_Ke.z;
        }
        else if (token == "Ni")
        {
            ss >> ma.m_Ni;
        }
        else if (token == "d")
        {
            ss >> ma.m_d;
        }
        else if (token == "illum")
        {
            ss >> ma.m_illum;
        }
        else if (token == "map_Kd")
        {
            std::filesystem::path texture_path;
            ss >> texture_path;

            ma.m_texture = std::make_unique<Texture>(texture_path);
        }
    }

    assert(material_attribute_name != "");
    m_materials[material_attribute_name] = std::move(ma);

    return true;
}