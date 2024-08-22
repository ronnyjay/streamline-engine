#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

namespace engine
{

class JSONObject;

class JSON
{
  public:
    static JSONObject parse(const std::filesystem::path &path);

  private:
    JSON() = default;

    static std::string read(const std::filesystem::path &);
    static std::string trim(const std::string &);
};

class JSONObject
{
  public:
    JSONObject() = default;

    inline std::string &operator[](const std::string &key)
    {
        return key_values_[key];
    }

    inline const bool contains(const std::string &key) const
    {
        return key_values_.contains(key);
    }

    template <typename T> [[nodiscard]] const T get(const std::string &key) const
    {
        T value;

        if (!(std::istringstream(key_values_.at(key)) >> value))
        {
            return T{};
        }

        return value;
    }

  private:
    std::unordered_map<std::string, std::string> key_values_;
};

} // namespace engine