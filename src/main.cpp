#include "core/application.hpp"

#include "math/matrix.hpp" // IWYU pragma: keep
#include "math/vector.hpp" // IWYU pragma: keep

using namespace engine;

//

Application gApplication;

//

int main(void)
{
    gApplication.Run();

    return 0;
}