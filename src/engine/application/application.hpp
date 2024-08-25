#pragma once

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
    application(game &g)
        : m_log("application")
        , m_game(g)
    {
    }

    void initialize();
    void run();

    ~application() = default;

    application(const application &) = delete;
    application(application &&) = delete;

    application &operator=(const application &) = delete;
    application &operator=(application &&) = delete;

  private:
    window m_window;

    logger m_log;

    game &m_game;

    static constexpr double MILLISECONDS_PER_UPDATE = 50;
    static constexpr double SECONDS_PER_UPDATE = MILLISECONDS_PER_UPDATE / 1000.0;
};

};
