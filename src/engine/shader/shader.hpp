#pragma once

#include <glad/gl.h>

#include <glm/glm.hpp>

#include <engine/components/components.hpp>
#include <string>

namespace engine
{

class ShaderProgram
{
  public:
    static constexpr size_t MAX_NUM_LIGHTS = 10;

    ShaderProgram()
    {
        m_ID = glCreateProgram();
    }

    operator unsigned int() const;

    void Use();

    bool Compile();

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
    void UpdateLights(const std::array<ShaderLight, ShaderProgram::MAX_NUM_LIGHTS> &lights);

    static ShaderProgram FromFile(const char *, const char *);

    bool AddShader(const std::string &path, GLint type);
    std::array<ShaderLight, ShaderProgram::MAX_NUM_LIGHTS> m_Lights;

  private:
    unsigned int m_ID;

    GLuint m_LightUBO;
    GLuint m_LightBlockBinding;

    bool CheckCompileErrors(unsigned int);
};

}; // namespace engine
