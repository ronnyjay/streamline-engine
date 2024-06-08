#pragma once

#include <glm/glm.hpp>

#include <string>

namespace engine
{

class Shader
{
  public:
    Shader()
    {
    }

    operator unsigned int() const;

    void Use();

    void Compile(const char *, const char *);

    void SetBool(const std::string &, bool) const;
    void SetInt(const std::string &, int) const;
    void SetUInt(const std::string &, int) const;
    void SetFloat(const std::string &, float) const;
    void SetVec2(const std::string &, const glm::vec2 &) const;
    void SetVec2(const std::string &, float, float) const;
    void SetVec3(const std::string &, const glm::vec3 &) const;
    void SetVec3(const std::string &, float, float, float) const;
    void SetVec4(const std::string &, const glm::vec4 &) const;
    void SetVec4(const std::string &, float, float, float, float);
    void SetMat2(const std::string &, const glm::mat2 &) const;
    void SetMat3(const std::string &, const glm::mat3 &) const;
    void SetMat4(const std::string &, const glm::mat4 &) const;

    static Shader FromFile(const char *, const char *);

  private:
    unsigned int m_ID;

    void CheckCompileErrors(unsigned int, std::string);
};

}; // namespace engine