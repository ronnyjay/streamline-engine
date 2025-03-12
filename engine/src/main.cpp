#include "engine.hpp" // IWYU pragma: keep

using namespace engine;

int main(void)
{
    application app;

    scene s;

    entity_type e = s.create();

    s.emplace<player_input>(e);
    s.emplace<player_look>(e);
    s.emplace<player_move>(e);

    s.tick(0);

    app.run();

    return 0;
}