#include <engine/logger/logger.hpp>
#include <engine/shader/shader.hpp>

#include <glad/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>

using namespace engine;

Shader::operator unsigned int() const
{
    return m_ID;
}

void Shader::Use()
{
    glUseProgram(m_ID);
}

void Shader::Compile(const char *vertexSource, const char *fragmentSource)
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    CheckCompileErrors(vertexShader, "Vertex");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    CheckCompileErrors(fragmentShader, "Fragment");

    // Create Shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);
    CheckCompileErrors(m_ID, "Program");

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::SetBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetUInt(const std::string &name, int value) const
{
    glUniform1ui(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
}

void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

Shader Shader::FromFile(const char *vertexPath, const char *fragmentPath)
{
    Logger::info("Loading vertex shader from file: %s\n", vertexPath);
    Logger::info("Loading fragment shader from file: %s\n", fragmentPath);

    Shader shader;

    std::string vShaderContents;
    std::string fShaderContents;

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
        Logger::err("Error reading shader file: %s\n", e.what());
    }

    shader.Compile(vShaderContents.c_str(), fShaderContents.c_str());

    return shader;
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];

    if (type != "Program")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);

            std::string longError(infoLog);
            std::string shortError(longError.substr(longError.find_last_of(':') + 2, longError.length()));

            Logger::warn("Shader compilation failed (%s): %s", type.c_str(), shortError.c_str());
        }
        else
        {
            Logger::info("Shader compilation success: (%s).\n", type.c_str());
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);

            std::string longError(infoLog);
            std::string shortError(longError.substr(longError.find_last_of(':') + 2, longError.length()));

            Logger::warn("Shader linking failed (%s): %s", type.c_str(), shortError.c_str());
        }
        else
        {
            Logger::info("Shader linking success: (%s).\n", type.c_str());
        }
    }
}