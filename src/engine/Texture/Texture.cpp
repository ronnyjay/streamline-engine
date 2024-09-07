#include <engine/Logger/Logger.hpp>
#include <engine/Texture/Texture.hpp>
#include <engine/stb/stb_image.hpp>

#include <string>

using namespace engine;

Texture::Texture()
    : m_Width(0)
    , m_Height(0)
    , m_InternalFormat(GL_RGB)
    , m_ImageFormat(GL_RGB)
    , m_Wrap_S(GL_REPEAT)
    , m_Wrap_T(GL_REPEAT)
    , m_FilterMin(GL_NEAREST)
    , m_FilterMax(GL_NEAREST)
{
    glGenTextures(1, &m_ID);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Generate(const unsigned int width, const unsigned int height, const unsigned char *data)
{
    m_Width  = width;
    m_Height = height;

    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_ImageFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_FilterMax);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Load(const std::basic_string<char> &path)
{
    Logger::info("Loading texture from file: %s\n", path.c_str());

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        switch (nrChannels)
        {
        case 1:
            m_InternalFormat = GL_RED;
            m_ImageFormat    = GL_RED;
            break;
        case 3:
            m_InternalFormat = GL_RGB;
            m_ImageFormat    = GL_RGB;
            break;
        case 4:
            m_InternalFormat = GL_RGBA;
            m_ImageFormat    = GL_RGBA;
            break;
        default:
            break;
        }

        Generate(width, height, data);

        // Free image data
        stbi_image_free(data);

        Logger::info("Texture loaded successfully.\n");
    }
    else
    {
        Logger::warn("Failed to load texture from file: %s\n", path.c_str());
    }
}
