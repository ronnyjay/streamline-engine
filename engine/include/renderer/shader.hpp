#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

#include "math/mat2x2.hpp" // IWYU pragma: keep
#include "math/mat3x3.hpp" // IWYU pragma: keep
#include "math/mat4x4.hpp" // IWYU pragma: keep
#include "math/vec2.hpp"   // IWYU pragma: keep
#include "math/vec3.hpp"   // IWYU pragma: keep
#include "math/vec4.hpp"   // IWYU pragma: keep

#include "../../vendor/glad/gl.h"

namespace engine
{

struct Shader
{

    Shader(const std::string &vertexPath, const std::string &fragmentPath);

    void bind()
    {
        glUseProgram(ID);
    }

    void unbind()
    {
        glUseProgram(0);
    }

    // clang-format off
    static constexpr size_t MAX_LIGHT_COUNT = 10;
    // clang-format on

    void setInt(const std::string &name, int value)
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value)
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setVec2(const std::string &name, const vec2 &value)
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, const vec3 &value)
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, const vec4 &value)
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setMat2(const std::string &name, const mat2 &value)
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void setMat3(const std::string &name, const mat3 &value)
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void setMat4(const std::string &name, const mat4 &value)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

  private:
    unsigned int ID;

    /** @brief */
    bool compile(const char *vertexSrc, const char *fragmentSrc);

    /**  @brief */
    bool checkCompileErrors(unsigned int shader, const char *type);
};

} // namespace engine