#include <engine/Application/Application.hpp>
#include <engine/Framebuffer/Framebuffer.hpp>
#include <engine/Logger/Logger.hpp>

#include <glad/gl.h>

namespace engine
{

Framebuffer::Framebuffer(const unsigned int width, const unsigned int height)
{
    m_Width = width;
    m_Height = height;

    m_Shader.AddShader("resources/shaders/framebuffer.vs", GL_VERTEX_SHADER);
    m_Shader.AddShader("resources/shaders/framebuffer.fs", GL_FRAGMENT_SHADER);
    m_Shader.Compile();

    m_Texture.m_FilterMin = GL_LINEAR;
    m_Texture.m_FilterMax = GL_LINEAR;
    m_Texture.Generate(width, height, nullptr);

    // clang-format off
    float vertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    // clang-format on

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);

    glGenRenderbuffers(1, &m_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Logger::Warn("Failed to initialize framebuffer.\n");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void Framebuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_Width, m_Height);
}

void Framebuffer::Render()
{
    m_Shader.Use();
    m_Texture.Bind();

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Framebuffer::Resize(const unsigned int width, const unsigned int height)
{
    Logger::Info("Resizing framebuffer: %dx%d.\n", width, height);

    if (width == m_Width && height == m_Height)
    {
        return;
    }

    m_Width = width;
    m_Height = height;

    m_Texture.Generate(width, height, nullptr);

    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Logger::Warn("Failed to initialize framebuffer.\n");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int Framebuffer::Width() const
{
    return m_Width;
}

int Framebuffer::Height() const
{
    return m_Height;
}

Framebuffer::~Framebuffer()
{
    glDeleteProgram(m_Shader);
    glDeleteTextures(1, (unsigned int *)&m_Texture);
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VAO);
    glDeleteRenderbuffers(1, &m_RBO);
    glDeleteFramebuffers(1, &m_FBO);
}

} // namespace engine
