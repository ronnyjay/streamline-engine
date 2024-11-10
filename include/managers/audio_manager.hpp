#pragma once

#include <core/singleton.hpp>

namespace engine
{

class AudioManager : public Singleton<AudioManager>
{
  public:
    void Init() override;
    void DeInit() override;
    void OnEvent(Event &e) override {};

    ~AudioManager() = default;
};

} // namespace engine
