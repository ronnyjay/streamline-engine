#include "texture.hpp"

#include <stb/stb_image.hpp>

#include <string>

using namespace engine;

texture::texture()
    : m_width(0)
    , m_height(0)
    , m_internal_format(GL_RGB)
    , m_image_format(GL_RGB)
    , m_wrap_s(GL_REPEAT)
    , m_wrap_t(GL_REPEAT)
    , m_filter_min(GL_NEAREST)
    , m_filter_max(GL_NEAREST)
    , m_log("texture")
{
    glGenTextures(1, &m_ID);
}

void texture::generate(const unsigned int width, const unsigned int height, const unsigned char *data)
{
    m_width = width;
    m_height = height;

    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, width, height, 0, m_image_format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_max);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture::load(const std::basic_string<char> &path)
{
    m_log.info("Loading texture from file: %s\n", path.c_str());

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        switch (nrChannels)
        {
        case 1:
            m_internal_format = GL_RED;
            m_image_format = GL_RED;
            break;
        case 3:
            m_internal_format = GL_RGB;
            m_image_format = GL_RGB;
            break;
        case 4:
            m_internal_format = GL_RGBA;
            m_image_format = GL_RGBA;
            break;
        default:
            break;
        }

        generate(width, height, data);

        // Free image data
        stbi_image_free(data);

        m_log.info("Texture loaded successfully.\n");
    }
    else
    {
        m_log.warn("Failed to load texture from file: %s\n", path.c_str());
    }
}
