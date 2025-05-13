#include "subsystems/display_manager.hpp"

#include "core/logger.hpp"
#include "core/window.hpp"

using namespace engine;

DisplayManager::DisplayManager()
{
    Logger::info("Detecting displays");

    int           count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        std::unique_ptr<Monitor> monitor = std::make_unique<Monitor>(monitors[i]);
        Logger::info("Found display: %s", monitor.get()->title);
        m_monitors.emplace_back(std::move(monitor));
    }
}

Monitor *const DisplayManager::getCurrentMonitor() const
{
    auto [windowX, windowY] = Window::getInstance().getPositionInScreen();

    for (size_t i = 0; i < m_monitors.size(); i++)
    {
        std::unique_ptr<Monitor> const &monitor = m_monitors[i];

        bool overlapX = windowX >= monitor->positionX && windowX < monitor->positionX + monitor->width;
        bool overlapY = windowY >= monitor->positionY && windowY < monitor->positionY + monitor->height;

        if (overlapX && overlapY)
        {
            return monitor.get();
        }
    }

    STREAMLINE_ASSERT(false, "Valid display not found");
}
