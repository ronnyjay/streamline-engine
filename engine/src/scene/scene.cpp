#include "scene/scene.hpp"

using namespace engine;

void scene::tick(double dt)
{
    auto view = m_registry.view<player_input, player_look, player_move>();

    for (const auto &entity : view)
    {
        auto [input, look, move] = view.get(entity);

        std::cout << input.dummy << std::endl;
        std::cout << look.dummy << std::endl;
        std::cout << move.dummy << std::endl;
    }
}

void scene::draw()
{
}
