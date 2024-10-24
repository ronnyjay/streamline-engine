#pragma once

#include "core/resource_manager.hpp"

#include <glad/gl.h>

namespace engine
{

class Texture : public Loadable
{
  public:
    Texture();

    std::string type;

    void        bind()
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    unsigned int id;

    unsigned int width;
    unsigned int height;

    unsigned int wrap_s;
    unsigned int wrap_t;

    unsigned int filter_min;
    unsigned int filter_max;

    unsigned int image_format;
    unsigned int internal_format;

    int          load(const std::string &path) override;

    void         generate(unsigned int, unsigned uint, const unsigned char *);
};

} // namespace engine