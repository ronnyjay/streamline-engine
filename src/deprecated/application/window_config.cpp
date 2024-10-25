#include "window_config.hpp"

#include <string>

logger window_config::log("window_config");

void window_config::load(const json_object &o)
{
    if (o.contains("setting.defaultres") && o.contains("setting.defaultresheight"))
    {
        width = o.get<int>("setting.defaultres");
        height = o.get<int>("setting.defaultresheight");
    }

    if (o.contains("setting.displaymode"))
    {
        auto val = o.get<std::string>("setting.displaymode");
        for (auto [mode, s] : display_modes_strings)
        {
            if (s == val)
            {
                display_mode = mode;
                goto displaymode_success;
            }
        }

    displaymode_failure:
        log.warn("Saved display mode did not match any display mode strings.\n");
    }

displaymode_success:

    if (o.contains("setting.monitor"))
    {
        monitor = o.get<std::string>("setting.monitor");
    }

    if (o.contains("setting.vsync"))
    {
        vsync = o.get<int>("setting.vsync");
    }
}
