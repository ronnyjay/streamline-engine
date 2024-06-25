#pragma once

#include <string>

namespace engine
{

class Identifier
{
  public:
    Identifier(const std::string &identifier)
        : m_Identifier(identifier)
    {
    }

    Identifier(const Identifier &) = default;

    const std::string &Get() const
    {
        return m_Identifier;
    }

    void Set(const std::string &identifier)
    {
        if (identifier != m_Identifier)
        {
            m_Identifier = identifier;
        }
    }

  private:
    std::string m_Identifier;
};

}; // namespace engine