#include "core/application.hpp"

using namespace engine;

//

Application gApplication;

//

int main(void)
{
    gApplication.GetDisplayManager()->SetDisplayMode(WindowMode::FullscreenBorderless);
    gApplication.Run();
}