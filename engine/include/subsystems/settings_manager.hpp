#pragma once

#include "core/singleton.hpp"

namespace engine
{

struct SettingsManager : public Singleton<SettingsManager>
{
    bool b_verticalSync;

    void save();
};

} // namespace engine