#include <engine/Config/Config.hpp>

#include <fstream>

using namespace engine;

Config::Config(std::filesystem::path path)
    : m_Path(path)
    , m_Directory(path.parent_path())
{
}

void Config::Load()
{
    Logger::Info("Loading configuration.\n");

    if (!std::filesystem::exists(m_Directory))
    {
        Logger::Warn("Directory not found: \"%s\".\n", m_Directory.c_str());

        if (std::filesystem::create_directories(m_Directory))
        {
            Logger::Info("Created directory: \"%s\".\n", m_Directory.c_str());
        }
        else
        {
            Logger::Err("Failed to create directory: \"%s\".\n", m_Directory.c_str());
        }
    }

    if (!std::filesystem::exists(m_Path))
    {
        Logger::Warn("File not found: \"%s\".\n", m_Path.filename().c_str());

        if (std::ofstream(m_Path))
        {
            Logger::Info("Created file: \"%s\".\n", m_Path.filename().c_str());
        }
        else
        {
            Logger::Err("Failed to create file: \"%s\".\n", m_Path.filename().c_str());
        }

        return;
    }

    std::ifstream file(m_Path);

    if (!file.is_open())
    {
        Logger::Warn("Failed to open file: \"%s\".\n", m_Path.filename().c_str());

        return;
    }

    std::string line;
    std::string key, value;
    std::istringstream stream;

    while (std::getline(file, line))
    {
        stream = std::istringstream(line);

        if (std::getline(stream, key, '\"') && std::getline(stream, key, '\"') && std::getline(stream, value, '\"') &&
            std::getline(stream, value, '\"'))
        {
            m_Values[key] = value;
        }
    }

    file.close();
}

void Config::Store()
{
    Logger::Info("Saving configuration.\n");

    std::ofstream file(m_Path);

    if (!file.is_open())
    {
        Logger::Warn("Failed to open file: \"%s\".\n", m_Path.filename().c_str());

        return;
    }

    file << "{\n";

    for (const auto &kv : m_Values)
    {
        file << "   \"" << kv.first << "\" \"" << kv.second << "\"\n";
    }

    file << "}\n";

    file.close();
}
