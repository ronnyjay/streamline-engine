#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace engine
{

class config
{
  public:
    config();
    config(const std::basic_string<char>);
    config &operator=(const config &);

    void add_path(const std::basic_string<char>);

    void set(const std::basic_string<char>, const std::basic_string<char>);
    void set(const config &);

    const bool has(const std::basic_string<char>);
    const std::basic_string<char> get(const std::basic_string<char>);

    void load();

  private:
    std::vector<std::basic_string<char>> m_paths;
    std::unordered_map<std::string, std::string> m_values;
};

}; // namespace engine