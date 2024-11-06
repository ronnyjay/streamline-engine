#include "renderer/shader.hpp"

#include "core/application.hpp"

#include <cstring>
#include <fstream>
#include <sstream>

using namespace engine;

bool Shader::add_shader(const std::string &path, unsigned int type)
{
    std::ifstream file;
    std::string   contents;

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
        // logger::warn("Error reading shader file: %s", e.what());
        return false;
    }

    unsigned int shader = glCreateShader(type);
    char        *source = const_cast<char *>(contents.c_str());

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    if (!check_compile_errors(shader))
    {
        return false;
    }

    glAttachShader(id, shader);
    glDeleteShader(shader);

    return true;
}

bool Shader::compile()
{
    GLint success;
    char  infoLog[1024];

    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 1024, NULL, infoLog);
        infoLog[strlen(infoLog) - 1] = '\0';

        // logger::warn("Shader program linking failed: %s", infoLog);

        return false;
    }

    return true;
}

bool Shader::check_compile_errors(unsigned int shader)
{
    int  success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        infoLog[strlen(infoLog) - 1] = '\0';

        // logger::err("Shader compilation failed: %s", infoLog);

        return false;
    }

    return true;
}
