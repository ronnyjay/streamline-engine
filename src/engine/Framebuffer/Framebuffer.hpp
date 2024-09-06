#pragma once

#include <engine/Shader/Shader.hpp>
#include <engine/Texture/Texture.hpp>

namespace engine
{

class Framebuffer
{
  public:
    Framebuffer(const unsigned int, const unsigned int);

    void Bind();
    void Unbind();

    void Render();

    void resize(const unsigned int, const unsigned int);

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

    ShaderProgram m_Shader;
    Texture m_Texture;
};

} // namespace engine