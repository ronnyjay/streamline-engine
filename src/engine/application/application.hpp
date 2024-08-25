#pragma once

#include "engine/framebuffer/framebuffer.hpp"
#include "engine/game/game.hpp"
#include "window.hpp"

#include <libstreamline/debug/logger.hpp>

namespace engine
{

/*
  A wrapper around an opengl/glfw instance
*/
class application
{
  public:
    application()
        : m_framebuffer(1280, 720)
        , m_log("application")
    {
    }

    void initialize(game &m_game);
    void run(game &m_game);

    ~application() = default;

    application(const application &) = delete;
    application(application &&) = delete;

    application &operator=(const application &) = delete;
    application &operator=(application &&) = delete;

  private:
    window m_window;
    framebuffer m_framebuffer;

    logger m_log;

    static constexpr double MILLISECONDS_PER_UPDATE = 50;
    static constexpr double SECONDS_PER_UPDATE = MILLISECONDS_PER_UPDATE / 1000.0;
};

};
