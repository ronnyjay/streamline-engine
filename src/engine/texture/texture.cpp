#include <engine/stb/stb_image.hpp>
#include <engine/texture/texture.hpp>

#include <iostream>

using namespace engine;

Texture2D::Texture2D(const char *file)
{
    unsigned char *data = stbi_load(file, &m_Width, &m_Height, &m_Channels, 0);

    if (data)
    {
        GLenum format = GL_NONE;

        switch (m_Channels)
        {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            break;
        }

        glGenTextures(1, &m_Id);

        glBindTexture(GL_TEXTURE_2D, m_Id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture: " << file << std::endl;
    }
}

void Texture2D::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture2D::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture2D::Width() const
{
    return m_Width;
}

int Texture2D::Height() const
{
    return m_Height;
}

int Texture2D::Channels() const
{
    return m_Channels;
}

unsigned int Texture2D::Id() const
{
    return m_Id;
}