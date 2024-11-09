#pragma once

#include "shader.hpp"
#include "texture.hpp"

namespace engine
{

class Framebuffer
{
  public:
    Framebuffer(int, int);

    void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    }

    void render();

    void unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void resize(unsigned int, unsigned int);

    int  width() const
    {
        return m_texture.width;
    }

    int height() const
    {
        return m_texture.height;
    }

    ~Framebuffer();

  private:
    Texture      m_texture;

    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_rbo;
    unsigned int m_fbo;

    Shader       m_shader;
};

} // namespace engine