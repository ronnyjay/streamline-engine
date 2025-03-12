#include "renderer/shader.hpp"

using namespace engine;

#include <fstream>
#include <sstream>

bool shader::addVertexShader(const std::string &path)
{
    std::string   vShaderContents;
    std::ifstream vShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        std::stringstream vShaderStream;

        vShaderFile.open(path);
        vShaderStream << vShaderFile.rdbuf();
        vShaderFile.close();

        vShaderContents = vShaderStream.str();
    }
    catch (std::ifstream::failure &e)
    {
        return false;
    }

    unsigned int vShader       = glCreateShader(GL_VERTEX_SHADER);
    char        *vShaderSource = const_cast<char *>(vShaderContents.c_str());

    glShaderSource(vShader, 1, &vShaderSource, NULL);

    glCompileShader(vShader);
    if (!checkCompileErrors(vShader, "VERTEX_SHADER"))
    {
        return false;
    }

    glAttachShader(ID, vShader);
    glDeleteShader(vShader);

    return true;
}

bool shader::addFragmentShader(const std::string &path)
{
    std::string   fShaderContents;
    std::ifstream fShaderFile;

    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        std::stringstream fShaderStream;

        fShaderFile.open(path);
        fShaderStream << fShaderFile.rdbuf();
        fShaderFile.close();

        fShaderContents = fShaderStream.str();
    }
    catch (std::ifstream::failure &e)
    {
        return false;
    }

    unsigned int fShader       = glCreateShader(GL_VERTEX_SHADER);
    char        *fShaderSource = const_cast<char *>(fShaderContents.c_str());

    glShaderSource(fShader, 1, &fShaderSource, NULL);

    glCompileShader(fShader);
    if (!checkCompileErrors(fShader, "FRAGMENT_SHADER"))
    {
        return false;
    }

    glAttachShader(ID, fShader);
    glDeleteShader(fShader);

    return true;
}

bool shader::compile(const std::string_view vertexSource, const std::string_view fragmentSource)
{
    glLinkProgram(ID);

    if (!checkCompileErrors(ID, "SHADER_PROGRAM"))
    {
        return false;
    }

    return true;
}

bool shader::checkCompileErrors(unsigned int shaderID, const std::string_view type)
{
    int  success;
    char infoLog[1024];

    if (std::string(type) != "SHADER_PROGRAM")
    {
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
            return false;
        }
    }
    else
    {
        glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);
            return false;
        }
    }

    return true;
}
