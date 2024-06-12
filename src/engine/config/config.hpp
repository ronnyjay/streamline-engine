#pragma once

#include <engine/logger/logger.hpp>

#include <filesystem>
#include <map>
#include <sstream>

namespace engine
{

class Config
{
  public:
    Config(std::filesystem::path);

    int Load();
    int Store();

    bool Has(const std::string &key)
    {
        return m_Values.contains(key);
    }

    template <typename T>
    T Get(const std::string &key) const
    {
        T value;

        std::istringstream stream(m_Values.at(key));

        if (!(stream >> value))
        {
            Logger::err("Type conversion failed for key: \"%s\".\n", key.c_str());

            return T{};
        }

        return value;
    }

    template <typename T>
    void Set(const std::string &key, T &value)
    {
        m_Values[key] = std::to_string(value);
    }

  private:
    std::filesystem::path m_Path;
    std::filesystem::path m_Directory;
    std::map<std::string, std::string> m_Values;
};

}; // namespace engine