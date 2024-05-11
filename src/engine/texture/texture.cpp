#include <engine/texture/texture.hpp>

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace engine;

std::vector<unsigned char> loadBMP(const std::filesystem::path &filepath, int &width, int &height)
{
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to load texture: " + filepath.string());
    }

    // Read BMP header
    file.seekg(18);
    file.read(reinterpret_cast<char *>(&width), 4);
    file.read(reinterpret_cast<char *>(&height), 4);

    int num_pixels = width * height;
    std::vector<unsigned char> data(num_pixels * 3); // 3 channels for RGB

    file.seekg(54); // Skip to pixel data
    file.read(reinterpret_cast<char *>(data.data()), data.size());

    // BMP uses BGR format, so swap red and blue channels
    for (int i = 0; i < num_pixels * 3; i += 3)
    {
        unsigned char temp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = temp;
    }

    return data;
}

Texture::Texture(const std::filesystem::path &image_path)
{
    std::vector<unsigned char> data;

    if (image_path.extension() == ".bmp")
    {
        m_channels = 3;
        data = loadBMP(image_path, m_width, m_height);
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        unsigned char *data = nullptr;
        data = stbi_load(image_path.c_str(), &m_width, &m_height, &m_channels, 4);

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