#pragma once

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
};

} // namespace engine
