#include "core/specification.hpp"
#include "core/application.hpp"

using namespace engine;

void Specification::OnInit(Application *const application) const
{
    application->GetWindow()->ShowMouse(true);
}

void Specification::OnExit(Application *const application) const
{
}