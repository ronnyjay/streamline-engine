#include "aim_trainer/aim_trainer.hpp"
#include "engine/application/application.hpp"

int main(int argc, char const *argv[])
{
    engine::application app;
    aim_trainer game;

    app.initialize(game);
    app.run(game);
}
