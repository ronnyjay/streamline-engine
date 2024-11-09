#pragma once

#include <core/singleton.hpp>

class AudioManager : public Singleton<AudioManager>
{
  public:
    void Init() override;
    void DeInit() override;

    ~AudioManager() = default;
};
