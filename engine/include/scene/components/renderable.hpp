#pragma once

#include "renderer/model.hpp"

namespace engine
{

struct Renderable
{
    Renderable(const std::shared_ptr<Model> model)
        : model(model)
    {
    }

    std::shared_ptr<Model> model;
};

} // namespace engine