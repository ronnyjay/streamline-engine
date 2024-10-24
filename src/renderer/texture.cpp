#include "texture.hpp"

#include <stb/stb_image.hpp>

using namespace engine;

Texture::Texture()
    : width(0)
    , height(0)
    , wrap_s(GL_REPEAT)
    , wrap_t(GL_REPEAT)
    , filter_min(GL_NEAREST)
    , filter_max(GL_NEAREST)
    , image_format(GL_RGB)
    , internal_format(GL_RGB)
{
    glGenTextures(1, &id);
}

void Texture::generate(unsigned int x, unsigned int y, const unsigned char *data)
{
    width  = x;
    height = y;

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);

    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::load(const std::string &path)
{
    int            x, y, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &x, &y, &nrChannels, 0);

    if (!data)
    {
        return 1;
    }

    switch (nrChannels)
    {
    case 1:
        internal_format = GL_RED;
        image_format    = GL_RED;
        break;
    case 3:
        internal_format = GL_RGB;
        image_format    = GL_RGB;
        break;
    case 4:
        internal_format = GL_RGBA;
        image_format    = GL_RGBA;
        break;
    default:
        break;
    }

    generate(x, y, data);
    stbi_image_free(data);

    return 0;
}