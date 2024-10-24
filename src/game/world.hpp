#pragma once

#include "core/exception.hpp"

#include "actor.hpp" // IWYU pragma: keep

namespace engine
{

class World
{
  public:
    /**
     * @brief Default constructor
     *
     */
    World()
    {
    }

    /**
     * @brief
     *
     */
    virtual void begin()
    {
        throw unimplemented_exception(std::source_location::current());
    };

    /**
     * @brief
     *
     * @param dt
     */
    virtual void update(float dt)
    {
        throw unimplemented_exception(std::source_location::current());
    };

    /**
     * @brief
     *
     */
    virtual void end()
    {
        throw unimplemented_exception(std::source_location::current());
    };

    /**
     * @brief Default destructor
     *
     */
    virtual ~World()
    {
    }

  private:
};

} // namespace engine