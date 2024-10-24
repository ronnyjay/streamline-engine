#pragma once

#include "actor.hpp"

#include <memory>
#include <vector>

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
        for (auto &actor : m_actors)
        {
            actor->begin();
        }
    }

    /**
     * @brief
     *
     * @param dt
     */
    virtual void update(float dt)
    {
        // Perform updates on all actors
        //
        // I.e. input, physics, etc.
    }

    /**
     * @brief
     *
     */
    virtual void end()
    {
        for (auto &actor : m_actors)
        {
            actor->end();
        }
    }

    template <typename T, typename... Args> std::shared_ptr<T> spawn_actor(Args &&...args)
    {
        // TODO: Potentially begin play here if actor is spawned after world start
        return m_actors.emplace_back(std::make_shared<T>(std::forward<Args>(args))...);
    }

    /**
     * @brief Default destructor
     *
     */
    virtual ~World()
    {
    }

  private:
    std::vector<std::shared_ptr<Actor>> m_actors;
};

} // namespace engine