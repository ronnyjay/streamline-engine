#include "core/renderer.hpp"
#include "core/window.hpp"

#include "scene/scene.hpp"

using namespace engine;

void Renderer::beginFrame()
{
    m_framebuffer.bind();

    setViewport(0, 0, m_framebuffer.width(), m_framebuffer.height());
    setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    enableDepth(true);
    clear();

    if (flags.b_showWireframes)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

void Renderer::endFrame()
{
    auto [windowWidth, windowHeight] = Window::getInstance().getSizeInScreen();

    m_framebuffer.unbind();

    setViewport(0, 0, windowWidth, windowHeight);
    setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    enableDepth(false);
    clear();

    if (flags.b_showWireframes)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    m_framebuffer.draw();
}
