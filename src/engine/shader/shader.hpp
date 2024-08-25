#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "libstreamline/debug/logger.hpp"

#include <string>

namespace engine
{

class shader_program
{
  public:
    static constexpr size_t MAX_NUM_LIGHTS = 10;

    shader_program()
        : m_log("shader_program")
    {
        m_ID = glCreateProgram();
    }

    operator unsigned int() const
    {
        return m_ID;
    }

    void bind() const
    {
        glUseProgram(m_ID);
    }

    void unbind() const
    {
        glUseProgram(0);
    }

    bool add_shader(const std::string &path, GLint type);

    bool compile();

    void set_bool(const std::string &name, bool value) const
    {
        bind();
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
        unbind();
    }

    void set_int(const std::string &name, int value) const
    {
        bind();
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
        unbind();
    }

    void set_uint(const std::string &name, int value) const
    {
        bind();
        glUniform1ui(glGetUniformLocation(m_ID, name.c_str()), value);
        unbind();
    }

    void set_float(const std::string &name, float value) const
    {
        bind();
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
        unbind();
    }

    void set_vec2(const std::string &name, const glm::vec2 &value) const
    {
        bind();
        glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
        unbind();
    }

    void set_vec2(const std::string &name, float x, float y) const
    {
        bind();
        glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
        unbind();
    }

    void set_vec3(const std::string &name, const glm::vec3 &value) const
    {
        bind();
        glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
    }

    void set_vec3(const std::string &name, float x, float y, float z) const
    {
        bind();
        glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
    }

    void set_vec4(const std::string &name, const glm::vec4 &value) const
    {
        bind();
        glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
    }

    void set_vec4(const std::string &name, float x, float y, float z, float w)
    {
        bind();
        glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
    }

    void set_mat2(const std::string &name, const glm::mat2 &mat) const
    {
        bind();
        glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void set_mat3(const std::string &name, const glm::mat3 &mat) const
    {
        bind();
        glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void set_mat4(const std::string &name, const glm::mat4 &mat) const
    {
        bind();
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

  private:
    unsigned int m_ID;
    logger m_log;

    bool check_compile_errors(unsigned int);
};

} // namespace engine
