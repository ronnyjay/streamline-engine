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

    /*
        Called every SECONDS_PER_UPDATE seconds.
        Generally used to update the physics of objects.
    */
    virtual void update() = 0;

    /**
      Called as often as possible, as long as a call to update
      has occurred in the last SECONDS_PER_UPDATE seconds.

      @param dt Because the render can happen on an uneven schedule,
      dt is passed as an interpolation between the previous
      update and the next one. This means an objects velocity*dt should
      be used to approximate the position on screen.
    **/
    virtual void render(double dt) = 0;
};

} // namespace engine
