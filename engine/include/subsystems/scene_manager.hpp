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
    std::shared_ptr<Scene> createScene()
    {
        return m_scenes.emplace_back(std::make_shared<Scene>());
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

    std::shared_ptr<Scene> currentScene()
    {
        if (!m_scenes.size())
        {
            STREAMLINE_ASSERT(false, "No scenes available,  perhaps try creating one...");
        }

        return m_scenes[m_currentScene];
    }

  private:
    std::vector<std::shared_ptr<Scene>> m_scenes;
};

} // namespace engine