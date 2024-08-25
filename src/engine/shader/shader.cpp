#include "shader.hpp"

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/gl.h>

using namespace engine;

bool shader_program::compile()
{
    GLint success;
    char infoLog[1024];

    glLinkProgram(m_ID);

    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ID, 1024, NULL, infoLog);

        m_log.warn("Linking failed: %s\n", infoLog);
        return false;
    }

    return true;
}

void shader_program::set_bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void shader_program::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void shader_program::set_uint(const std::string &name, int value) const
{
    glUniform1ui(glGetUniformLocation(m_ID, name.c_str()), value);
}

void shader_program::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void shader_program::set_vec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void shader_program::set_vec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
}

void shader_program::set_vec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void shader_program::set_vec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
}

void shader_program::set_vec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void shader_program::set_vec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
}

void shader_program::set_mat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void shader_program::set_mat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void shader_program::set_mat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

bool shader_program::check_compile_errors(unsigned int shader)
{
    int success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);

        m_log.err("Compilation failed: %s\n", infoLog);
        return false;
    }

    return true;
}

bool shader_program::add_shader(const std::string &path, GLint shaderType)
{
    std::ifstream file;
    std::string contents;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(path);

        std::stringstream ss;

        ss << file.rdbuf();

        contents = ss.str();
    }
    catch (std::ifstream::failure &e)
    {
        m_log.err("Error reading shader file: %s\n", e.what());
        return false;
    }

    unsigned int shader = glCreateShader(shaderType);
    char *source = const_cast<char *>(contents.c_str());

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    if (!check_compile_errors(shader))
    {
        return false;
    }

    glAttachShader(m_ID, shader);

    glDeleteShader(shader);

    return true;
}
