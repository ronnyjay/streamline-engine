#include <engine/Config/Config.hpp>

using namespace engine;

Config::Config()
{
}

void Config::from_json(const JSONObject &json)
{
    if (json.contains("setting.defaultres"))
    {
        defaultres = json.get<int>("setting.defaultres");
    }

    if (json.contains("setting.defaultresheight"))
    {
        defaultresheight = json.get<int>("setting.defaultresheight");
    }

    if (json.contains("setting.displaymode"))
    {
        displaymode = json.get<int>("setting.displaymode");
    }

    if (json.contains("setting.monitor"))
    {
        monitor = json.get<int>("setting.monitor");
    }

    if (json.contains("setting.vsync"))
    {
        vsync = json.get<int>("setting.vsync");
    }
}