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

        m_log.warn("Linking failed: %s", infoLog);
        return false;
    }

    return true;
}

bool shader_program::check_compile_errors(unsigned int shader)
{
    int success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);

        m_log.err("Compilation failed: %s", infoLog);
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
        m_log.err("Error reading shader file: %s", e.what());
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
