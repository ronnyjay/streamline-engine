#pragma once

#include <engine/Logger/Logger.hpp>

#include <filesystem>
#include <map>
#include <sstream>

namespace engine
{

class Config
{
  public:
    Config(std::filesystem::path);

    void Load();
    void Store();

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

    bool Has(const std::string &key)
    {
        return m_Values.contains(key);
    }

  private:
    std::filesystem::path m_Path;
    std::filesystem::path m_Directory;
    std::map<std::string, std::string> m_Values;
};

} // namespace engine