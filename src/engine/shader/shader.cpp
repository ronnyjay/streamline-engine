#include <engine/logger/logger.hpp>
#include <engine/shader/shader.hpp>

#include <glad/gl.h>

#include <array>
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
    if (m_LightBlockBinding != GL_INVALID_INDEX)
        glBindBuffer(GL_UNIFORM_BUFFER, m_LightUBO);
}

bool Shader::Compile(const char *vertexSource, const char *fragmentSource)
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    if (!CheckCompileErrors(vertexShader, "Vertex"))
    {
        return false;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    if (!CheckCompileErrors(fragmentShader, "Fragment"))
    {
        return false;
    }

    // Create Shader Program
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);
    if (!CheckCompileErrors(m_ID, "Program"))
    {
        return false;
    }

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Add uniform buffer
    m_LightBlockBinding = glGetUniformBlockIndex(m_ID, "LightBlock");
    if (m_LightBlockBinding != GL_INVALID_INDEX)
    {
        glUniformBlockBinding(m_ID, m_LightBlockBinding, 0);

        glGenBuffers(1, &m_LightUBO);
        glBindBuffer(GL_UNIFORM_BUFFER, m_LightUBO);
        glBufferData(GL_UNIFORM_BUFFER, m_Lights.size() * sizeof(ShaderLight), NULL, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_LightUBO, 0, m_Lights.size() * sizeof(ShaderLight));
    }

    return true;
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

void Shader::UpdateLights(const std::array<ShaderLight, Shader::MAX_NUM_LIGHTS> &lights)
{
    std::copy(lights.cbegin(), lights.cend(), m_Lights.begin());
    glBindBuffer(GL_UNIFORM_BUFFER, m_LightUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, Shader::MAX_NUM_LIGHTS * sizeof(ShaderLight), m_Lights.data());
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

    if (!shader.Compile(vShaderContents.c_str(), fShaderContents.c_str()))
    {
        throw std::runtime_error("Error compiling shaders.");
    }

    return shader;
}

bool Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];

    if (type != "Program")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);

            Logger::err("Shader compilation failed (%s): %s", type.c_str(), infoLog);
            return false;
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

            Logger::warn("Shader linking failed (%s): %s\n", infoLog);
            return false;
        }
        else
        {
            Logger::info("Shader linking success: (%s).\n", type.c_str());
        }
    }

    return true;
}
