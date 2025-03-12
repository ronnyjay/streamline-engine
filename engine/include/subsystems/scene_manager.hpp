#pragma once

#include "core/singleton.hpp"

#include "scene/scene.hpp"

namespace engine
{

struct scene_manager : public singleton<scene_manager>
{
};

} // namespace engine