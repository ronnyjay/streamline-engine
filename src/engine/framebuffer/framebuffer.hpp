#pragma once

#include <engine/shader/shader.hpp>
#include <engine/texture/texture.hpp>

namespace engine
{

class Framebuffer
{
  public:
    Framebuffer(const int, const int);

    void Bind();
    void Unbind();

    void Draw();

    void Resize(const int, const int);

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