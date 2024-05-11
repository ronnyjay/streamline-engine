#include <engine/texture/texture.hpp>

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace engine;

Texture::Texture(const std::filesystem::path &image_path)
{
    unsigned char *data = nullptr;
    data = stbi_load(image_path.c_str(), &m_width, &m_height, &m_channels, 0); // desired channels to 0 to load with original number of channels

    if (!data)
    {
        throw std::runtime_error("Failed to load texture: " + image_path.string());
    }

    GLint internalformat;
    switch (m_channels)
    {
    case 3:
        internalformat = GL_RGB;
        break;
    case 4:
        internalformat = GL_RGBA;
        break;
    default:
        throw std::runtime_error("Unhandled channel size for texture: " + image_path.string());
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, internalformat, m_width, m_height, 0, internalformat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::get_id() const
{
    return m_id;
}

Texture::~Texture()
{
}