#include "core/application.hpp"
#include "core/displaymanager.hpp"

using namespace engine;

//

Application    gApplication;
DisplayManager gDisplayManager;

//

int main(void)
{
    gDisplayManager.StartUp();

    gApplication.Run();

    gDisplayManager.ShutDown();
}