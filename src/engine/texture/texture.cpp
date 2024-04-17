#include <engine/texture/texture.hpp>

#include <stdexcept>

using namespace engine;

texture::texture(const std::basic_string<char> image_path)
{
    unsigned char *data = stbi_load(image_path.c_str(), &m_width, &m_height, &m_channels, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
        throw std::runtime_error("Unhandled channel size for texture: " + image_path);
    }

    if (data)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, internalformat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        throw std::runtime_error("Failed to load texture: " + image_path);
    }

    stbi_image_free(data);
}

void texture::bind()
{
    glBindTexture(GL_TEXTURE_BINDING_2D, m_id);
}

GLuint texture::id() const
{
    return m_id;
}

texture::~texture()
{
}