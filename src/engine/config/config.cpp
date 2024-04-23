#include <engine/config/config.hpp>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace engine;

config::config()
{
}

config::config(const std::basic_string<char> path)
{
    add_path(path);
}

config &config::operator=(const config &other)
{
    set(other);
    return *this;
}

void config::add_path(const std::basic_string<char> path)
{
    m_paths.emplace_back(path);
}

void config::set(const std::basic_string<char> key, const std::basic_string<char> value)
{
    if (m_values.find(key) != m_values.end())
    {
        return;
    }

    m_values[key] = value;
}

void config::set(const config &other)
{
    if (this == &other)
    {
        return;
    }

    m_values = other.m_values;
    m_paths = other.m_paths;
}

const bool config::has(const std::basic_string<char> key)
{
    return (m_values.find(key) != m_values.end());
}

const std::basic_string<char> config::get(const std::basic_string<char> key)
{
    if (!has(key))
    {
        throw std::runtime_error("Configuration variable not found: " + key);
    }

    return m_values.find(key)->second;
}

void config::load()
{
    for (auto it = m_paths.rbegin(); it != m_paths.rend(); ++it)
    {
        if (!std::filesystem::exists(*it))
        {
            continue;
        }

        std::ifstream file(*it);

        if (!file.is_open())
        {
            throw std::runtime_error("Error opening configuration file");
        }

        std::string line;
        std::string key, value;
        std::istringstream stream;

        while (std::getline(file, line))
        {
            stream = std::istringstream(line);

            while (stream >> key >> value)
            {
                set(key, value);
            }
        }

        file.close();
    }
}
