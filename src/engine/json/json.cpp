#include "engine/json/json.hpp"
#include "engine/logger/logger.hpp"

#include <fstream>

json_object json::parse(const std::filesystem::path &path)
{
    json_object obj;

    std::string raw_json = read(path);
    std::string trimmed_json = trim(raw_json);

    if (trimmed_json.front() == '{' && trimmed_json.back() == '}')
    {
        trimmed_json = trimmed_json.substr(1, trimmed_json.length() - 2);
    }
    else
    {
        std::exit(1);
    }

    std::stringstream stream(trimmed_json);
    std::string item;

    while (std::getline(stream, item, ','))
    {
        item = trim(item);

        size_t delim = item.find(':');

        if (delim == std::string::npos)
        {
            std::exit(1);
        }

        std::string key = trim(item.substr(0, delim));
        std::string value = trim(item.substr(delim + 1));

        if (key.front() == '"' && key.back() == '"')
        {
            key = key.substr(1, key.size() - 2);
        }

        if (value.front() == '"' && value.back() == '"')
        {
            value = value.substr(1, value.size() - 2);
        }

        logger::info("Got Key: %s, Got Value: %s\n", key.c_str(), value.c_str());

        obj[key] = value;
    }

    return obj;
}

std::string json::read(const std::filesystem::path &path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::exit(1);
    }

    return (std::stringstream() << file.rdbuf()).str();
}

std::string json::trim(const std::string &data)
{

    size_t first_char = data.find_first_not_of(" t\n\r\f\v");
    size_t last_char = data.find_last_not_of(" t\n\r\f\v");

    return data.substr(first_char, (last_char - first_char + 1));
}