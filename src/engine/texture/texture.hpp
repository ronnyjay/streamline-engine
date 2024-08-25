#pragma once

#include "libstreamline/debug/logger.hpp"
#include <engine/resource_manager/resource_manager.hpp>
#include <glad/gl.h>

#include <string>

namespace engine
{

class texture : public loadable
{
  public:
    texture();

    operator unsigned int() const
    {
        return m_ID;
    }

    void bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

    void unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void generate(const unsigned int, const unsigned int, const unsigned char *);

    unsigned int m_width;
    unsigned int m_height;

    unsigned int m_internal_format;
    unsigned int m_image_format;

    unsigned int m_wrap_s;
    unsigned int m_wrap_t;
    unsigned int m_filter_min;
    unsigned int m_filter_max;

    std::string m_Type;

    void load(const std::basic_string<char> &path) override;

  private:
    unsigned int m_ID;
    logger m_log;
};

} // namespace engine