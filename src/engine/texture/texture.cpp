#include <engine/stb/stb_image.hpp>
#include <engine/texture/texture.hpp>

#include <iostream>

using namespace engine;

Texture::Texture()
    : m_Width(0), m_Height(0), m_InternalFormat(GL_RGB), m_ImageFormat(GL_RGB), m_Wrap_S(GL_REPEAT), m_Wrap_T(GL_REPEAT),
      m_FilterMin(GL_NEAREST), m_FilterMax(GL_NEAREST)

{
    glGenTextures(1, &m_ID);
}

Texture::operator unsigned int() const
{
    return m_ID;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Generate(const unsigned int width, const unsigned int height, const unsigned char *data)
{
    m_Width = width;
    m_Height = height;

    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_ImageFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_FilterMax);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture Texture::FromFile(const char *file)
{
    Texture texture;

    int width, height, nrChannels;
    unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);

    if (data)
    {
        switch (nrChannels)
        {
        case 1:
            texture.m_InternalFormat = GL_RED;
            texture.m_ImageFormat = GL_RED;
            break;
        case 3:
            texture.m_InternalFormat = GL_RGB;
            texture.m_ImageFormat = GL_RGB;
            break;
        case 4:
            texture.m_InternalFormat = GL_RGBA;
            texture.m_ImageFormat = GL_RGBA;
            break;
        default:
            break;
        }

        texture.Generate(width, height, data);

        // Free image data
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture: " << file << std::endl;
    }

    return texture;
}