#pragma once

#include "core/singleton.hpp"

namespace engine
{

struct input_manager : public singleton<input_manager>
{
};

} // namespace engine