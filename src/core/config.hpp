#pragma once

#include "core/exception.hpp"
#include "core/logger.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

class Config
{
  public:
    /**
     * @brief
     *
     */
    Config() = default;

    /**
     * @brief
     *
     * @param path
     */
    Config(const std::filesystem::path &path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            std::exit(1);
        }

        std::string key, value;

        while (file >> key >> value)
        {
            m_key_values[key] = value;
        }
    }

    /**
     * @brief
     *
     * @param key
     * @return std::string&
     */
    inline std::string &operator[](const std::string &key)
    {
        return m_key_values[key];
    }

    /**
     * @brief
     *
     * @param key
     * @return true
     * @return false
     */
    inline const bool contains(const std::string &key) const
    {
        return m_key_values.contains(key);
    }

    /**
     * @brief
     *
     * @tparam T
     * @param key
     * @return const T
     */
    template <typename T> [[nodiscard]] const T get(const std::string &key) const
    {
        T value;

        if (!(std::istringstream(m_key_values.at(key)) >> value))
        {
            return T{};
        }

        return value;
    }

    /**
     * @brief
     *
     * @return Config
     */
    static Config load(const std::filesystem::path &);

  private:
    std::unordered_map<std::string, std::string> m_key_values;
};
