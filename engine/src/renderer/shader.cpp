#include "renderer/shader.hpp"

#include <fstream>
#include <sstream>

#include "assert.hpp"

using namespace engine;

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
    : ID(glCreateProgram())
{
    std::string   vShaderContents;
    std::string   fShaderContents;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vShaderContents = vShaderStream.str();
        fShaderContents = fShaderStream.str();
    }
    catch (std::ifstream::failure &e)
    {
        STREAMLINE_ASSERT(false, "Failed to load shader");
    }

    compile(vShaderContents.c_str(), fShaderContents.c_str());
}

bool Shader::compile(const char *vertexSource, const char *fragmentSource)
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    if (!checkCompileErrors(vertexShader, "Vertex"))
    {
        std::cerr << "Failed to compile vertex shader" << std::endl;
        return false;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    if (!checkCompileErrors(fragmentShader, "Fragment"))
    {
        std::cerr << "Failed to compile fragment shader" << std::endl;
        return false;
    }

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    if (!checkCompileErrors(ID, "Program"))
    {
        std::cerr << "Failed to compile shader program" << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

bool Shader::checkCompileErrors(unsigned int shader, const char *type)
{
    int  success;
    char infoLog[1024];

    if (std::string(type) != "Program")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf("%s", infoLog);
            return false;
        }
        else
        {
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("%s", infoLog);
            return false;
        }
        else
        {
        }
    }

    return true;
}