#pragma once

#include "core/singleton.hpp"

#include "scene/scene.hpp"

namespace engine
{

struct SceneManager : public Singleton<SceneManager>
{
  private:
    uint32_t m_currentScene = 0;

  public:
    std::shared_ptr<scene> createScene()
    {
        return m_scenes.emplace_back(std::make_shared<scene>());
    }

    void nextScene()
    {
        if (m_currentScene == m_scenes.size() - 1)
        {
            m_currentScene = 0;
        }
        else
        {
            ++m_currentScene;
        }
    }

    void prevScene()
    {
        if (m_currentScene == 0)
        {
            m_currentScene = m_scenes.size() - 1;
        }
        else
        {
            --m_currentScene;
        }
    }

    std::shared_ptr<scene> currentScene()
    {
        // todo: maybe remove assertion, return nullptr?
        //
        // benefits of asserting include making the user aware there is nothing to
        // simulatate/render, thus they know early-on why they are not seeing anything on screen
        //
        // but should this be a requirement?
        if (!m_scenes.size())
        {
            STREAMLINE_ASSERT(false, "No scenes available. Perhaps try creating one");
        }

        return m_scenes[m_currentScene];
    }

  private:
    std::vector<std::shared_ptr<scene>> m_scenes;
};

} // namespace engine