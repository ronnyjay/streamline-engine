#pragma once

#include <engine/shader/shader.hpp>

namespace engine
{

class Framebuffer
{
  public:
    Framebuffer()
    {
    }

    void Initialize(int, int);
    void Resize(int, int);

    void Bind();
    void Unbind();

    void Draw();

    ~Framebuffer();

  private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_RBO;
    unsigned int m_FBO;
    unsigned int m_Width;
    unsigned int m_Height;
    unsigned int m_Texture;
    std::unique_ptr<Shader> m_Shader;
};

}; // namespace engine