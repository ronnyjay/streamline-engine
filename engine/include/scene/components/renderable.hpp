#pragma once

#include "renderer/model.hpp"

#include "subsystems/resource_manager.hpp"

namespace engine
{

struct Renderable
{
    Renderable(const std::string &path)
        : model(ResourceManager::getInstance().getModel(path))
    {
    }

    Renderable(const std::shared_ptr<Model> model)
        : model(model)
    {
    }

    std::shared_ptr<Model> model;
};

} // namespace engine