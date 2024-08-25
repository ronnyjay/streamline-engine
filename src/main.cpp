#include "aim_trainer/aim_trainer.hpp"
#include "engine/application/application.hpp"

int main(int argc, char const *argv[])
{
    aim_trainer game;
    engine::application app(game);
    app.initialize();
    app.run();
}
