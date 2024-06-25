#pragma once

#include <engine/ResourceManager/ResourceManager.hpp>
#include <glad/gl.h>

#include <string>

namespace engine
{

class Texture : public Loadable
{
  public:
    Texture();

    operator unsigned int() const
    {
        return m_ID;
    }

    void Bind();

    void Generate(const unsigned int, const unsigned int, const unsigned char *);

    unsigned int m_Width;
    unsigned int m_Height;

    unsigned int m_InternalFormat;
    unsigned int m_ImageFormat;

    unsigned int m_Wrap_S;
    unsigned int m_Wrap_T;
    unsigned int m_FilterMin;
    unsigned int m_FilterMax;

    std::string m_Type;

    void Load(const std::basic_string<char> &path) override;

  private:
    unsigned int m_ID;
};

} // namespace engine