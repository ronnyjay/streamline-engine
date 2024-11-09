#include "renderer/renderer.hpp"

using namespace engine;

void Renderer::OnViewportResize(int width, int height)
{
    mFramebuffer.resize(width, height);
}

void Renderer::Render(int width, int height)
{
    mFramebuffer.bind();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, mFramebuffer.width(), mFramebuffer.height());

    // Render scene
    // ...

    mFramebuffer.unbind();

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    mFramebuffer.render();
}
