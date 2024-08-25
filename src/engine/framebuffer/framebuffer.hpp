#pragma once

#include "engine/shader/shader.hpp"
#include "engine/texture/texture.hpp"

namespace engine
{

class framebuffer
{
  public:
    framebuffer(const unsigned int, const unsigned int);

    void bind();
    void unbind();

    void render();

    void resize(const unsigned int, const unsigned int);

    ~framebuffer();

  private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_rbo;
    unsigned int m_fbo;

    shader_program m_shader;
    texture m_texture;
    logger m_log;
};

} // namespace engine