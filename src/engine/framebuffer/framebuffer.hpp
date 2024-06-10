#pragma once

#include <engine/shader/shader.hpp>
#include <engine/texture/texture.hpp>

namespace engine
{

class Framebuffer
{
  public:
    Framebuffer(const unsigned int, const unsigned int);

    void Bind();
    void Unbind();

    void Render();

    void Resize(const unsigned int, const unsigned int);

    int Width() const;
    int Height() const;

    ~Framebuffer();

  private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_RBO;
    unsigned int m_FBO;
    unsigned int m_Width;
    unsigned int m_Height;

    Shader m_Shader;
    Texture m_Texture;
};

}; // namespace engine