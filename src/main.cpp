#include "engine/application/application.hpp"

int main(int argc, char const *argv[])
{
    application app;
    app.initialize();
    app.run();
}
