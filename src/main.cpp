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

    if (!gDisplayManager.SetPreferredMonitorIndex(1010))
    {
        printf("Monitor not found...\n");
    }

    gApplication.Run();

    gDisplayManager.ShutDown();
}