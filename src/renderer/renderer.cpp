#include "renderer/renderer.hpp"

using namespace engine;

void Renderer::on_viewport_resize(int width, int height)
{
    m_framebuffer.resize(width, height);
}

void Renderer::render(int width, int height)
{
    m_framebuffer.bind();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_framebuffer.width(), m_framebuffer.height());

    // Render scene
    // ...

    m_framebuffer.unbind();

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    m_framebuffer.render();
}
