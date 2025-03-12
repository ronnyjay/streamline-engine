#include "renderer/texture.hpp"
#include "assert.hpp"

#include <stb/stb_image.hpp>

using namespace engine;

texture::texture(const std::string_view path)
    : type(texture_type::NONE)
{
    int nrChannels      = 0;
    int imageFormat     = 0;
    int internalFormat  = 0;
    unsigned char *data = stbi_load(path.data(), &width, &height, &nrChannels, 0);

    STREAMLINE_ASSERT(data != nullptr, std::string("failed to load image data:") + path.data());

    switch (nrChannels)
    {
    case 1:
        internalFormat = GL_RED;
        imageFormat    = GL_RED;
        format         = texture_format::RED;
        break;
    case 3:
        internalFormat = GL_RGB;
        imageFormat    = GL_RGB;
        format         = texture_format::RGB;
        break;
    case 4:
        internalFormat = GL_RGBA;
        imageFormat    = GL_RGBA;
        format         = texture_format::RGBA;
        break;
    default:
        break;
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
}
