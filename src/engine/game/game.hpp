#pragma once

#include <glm/glm.hpp>

namespace engine
{

class game
{
  public:
    game() = default;
    ~game() = default;

    game(const game &) = delete;
    game(game &&) = delete;

    game &operator=(const game &) = delete;
    game &operator=(game &&) = delete;

    /**
      Generally used to update the physics of objects.
      Called as many times in a row as necessary to keep
      up with real time before a render occurs.

      @param dt The engine's SECONDS_PER_UPDATE
    **/
    virtual void update(double dt) = 0;

    /**
      Called after update has caught up with real time.

      @param dt Because the render can happen on an uneven schedule,
      dt is passed as an interpolation between the previous
      update and the next one. This means an objects velocity*dt should
      be used to approximate the position on screen.
    **/
    virtual void render(double dt) = 0;

    /**
      Called when the window dimensions change

      @param width New window width
      @param height New window height
    **/
    virtual void window_size_changed(const unsigned int width, const unsigned int height) = 0;

    /**
      Called when a mouse press event occurs
    **/
    virtual void mouse_press(const int button, const int action, const int mods) = 0;

    /**
      Called when a cursor event occurs
    **/
    virtual void mouse_pos(const double x, const double y)
    {
        m_mouse_pos.x = x;
        m_mouse_pos.y = y;
    }

    /*
      Should quit?
    */
    bool should_quit() const
    {
        return m_should_quit;
    }

    /*
      Gracefully stop the game
    */
    void quit()
    {
    }

  protected:
    bool m_should_quit = false;
    glm::vec3 m_mouse_pos;
};

} // namespace engine
