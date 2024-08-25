#pragma once

#include "libstreamline/debug/logger.hpp"
#include <engine/shader/shader.hpp>
#include <engine/texture/texture.hpp>

namespace engine
{

class framebuffer
{
  public:
    framebuffer(const unsigned int width, const unsigned int height);

    void deinit();
    void bind();
    void unbind();
    void render();
    void resize(const unsigned int, const unsigned int);

    ~framebuffer() = default;

    unsigned int m_width;
    unsigned int m_height;

  private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_rbo;
    unsigned int m_fbo;

    logger m_log;
    shader_program m_shader;
    unsigned int m_texture;
};

}; // namespace engine