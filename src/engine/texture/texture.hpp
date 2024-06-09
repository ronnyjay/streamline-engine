#pragma once

#include <glad/gl.h>

#include <string>

namespace engine
{

class Texture
{
  public:
    Texture();

    operator unsigned int() const;

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

    static Texture FromFile(const char *);

  private:
    unsigned int m_ID;
};

class MaterialTexture : public Texture
{
  public:
    MaterialTexture() : Texture()
    {
    }

    std::string m_Path;
    std::string m_Type;

    static MaterialTexture FromFile(const char *path, const char *directory)
    {
        auto filename = std::string(directory) + '/' + std::string(path);

        return MaterialTexture(Texture::FromFile(filename.c_str()), path);
    }

  private:
    MaterialTexture(const Texture texture, const char *path) : Texture(texture), m_Path(path)
    {
    }
};

}; // namespace engine