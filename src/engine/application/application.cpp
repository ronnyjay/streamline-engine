#include "application.hpp"

application *application::ref = nullptr;

// probabably a better way of doing this ...
void application::on_event(const event &e)
{
    switch (e.type())
    {
    case event_type::None:
        break;
    case event_type::KeyEvent:
        break;
    case event_type::MouseEvent:
        break;
    case event_type::WindowCloseEvent:
        break;
    case event_type::WindowResizeEvent:
        break;
    }
}
