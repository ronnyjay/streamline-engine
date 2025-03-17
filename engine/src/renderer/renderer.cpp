#include "core/renderer.hpp"
#include "scene/scene.hpp"

using namespace engine;

void Renderer::begin(const std::shared_ptr<scene> &s)
{
    // Draw for now
    // Add framebuffer later
    s.get()->draw();
}