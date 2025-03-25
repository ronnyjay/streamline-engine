#pragma once

#include <cstdint>
#include <memory>

namespace engine
{

struct Shader;

struct Framebuffer
{
    Framebuffer(uint32_t width, uint32_t height);
    ~Framebuffer();

    void     draw();

    void     bind();
    void     unbind();

    uint32_t width() const
    {
        return m_width;
    }

    uint32_t height() const
    {
        return m_height;
    }

    void resize(uint32_t width, uint32_t height);

  private:
    unsigned int            m_VAO;
    unsigned int            m_VBO;
    unsigned int            m_RBO;
    unsigned int            m_FBO;
    unsigned int            m_TEX;
    std::shared_ptr<Shader> m_SHP;

    unsigned int            m_width;
    unsigned int            m_height;
};

} // namespace engine