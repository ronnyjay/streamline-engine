#include "core/renderer.hpp"
#include "core/application.hpp"
#include "scene/scene.hpp"
#include <GLFW/glfw3.h>

using namespace engine;

void Renderer::begin(const std::shared_ptr<scene> &s)
{
    int width, height;
    glfwGetFramebufferSize(Application::getInstance().getWindow()->operator GLFWwindow *(), &width, &height);

    m_framebuffer.bind();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_framebuffer.width(), m_framebuffer.height());

    if (flags.b_showWireframes)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    s.get()->draw();

    m_framebuffer.unbind();
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    if (flags.b_showWireframes)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    m_framebuffer.draw();
}