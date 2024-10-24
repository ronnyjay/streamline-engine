#include "config.hpp"

#include <fstream>

Config Config::load(const std::filesystem::path &path)
{
    Config        cfg;

    std::ifstream file(path);
    if (!file.is_open())
    {
        std::exit(1);
    }

    std::string key, value;
    while (file >> key >> value)
    {
        cfg[key] = value;
    }

    return cfg;
}