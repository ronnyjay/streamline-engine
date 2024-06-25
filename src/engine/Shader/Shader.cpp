#include <engine/Logger/Logger.hpp>
#include <engine/Shader/Shader.hpp>

#include <glad/gl.h>

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace engine;

ShaderProgram::operator unsigned int() const
{
    return m_ID;
}

void ShaderProgram::Use()
{
    glUseProgram(m_ID);
    if (m_LightBlockBinding != GL_INVALID_INDEX)
        glBindBuffer(GL_UNIFORM_BUFFER, m_LightUBO);
}

bool ShaderProgram::Compile()
{
    GLint success;
    char infoLog[1024];

    glLinkProgram(m_ID);

    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ID, 1024, NULL, infoLog);

        Logger::warn("Shader program linking failed: %s\n", infoLog);
        return false;
    }

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

void ShaderProgram::SetBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void ShaderProgram::SetInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void ShaderProgram::SetUInt(const std::string &name, int value) const
{
    glUniform1ui(glGetUniformLocation(m_ID, name.c_str()), value);
}

void ShaderProgram::SetFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void ShaderProgram::SetVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::SetVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
}

void ShaderProgram::SetVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::SetVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
}

void ShaderProgram::SetVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::SetVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
}

void ShaderProgram::SetMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::SetMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::UpdateLights(const std::array<ShaderLight, ShaderProgram::MAX_NUM_LIGHTS> &lights)
{
    std::copy(lights.cbegin(), lights.cend(), m_Lights.begin());
    glBindBuffer(GL_UNIFORM_BUFFER, m_LightUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, ShaderProgram::MAX_NUM_LIGHTS * sizeof(ShaderLight), m_Lights.data());
}

/*
Shader Shader::FromFile(const char *vertexPath, const char *fragmentPath)
{
    Logger::info("Loading vertex shader from file: %s\n", vertexPath);
    Logger::info("Loading fragment shader from file: %s\n", fragmentPath);

    Shader shader;

    std::string vShaderContents;

    std::ifstream fShaderFile;

    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


    if (!shader.Compile(vShaderContents.c_str(), fShaderContents.c_str()))
    {
        throw std::runtime_error("Error compiling shaders.");
    }

    return shader;
}
*/

bool ShaderProgram::CheckCompileErrors(unsigned int shader)
{
    int success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);

        Logger::err("Shader compilation failed: %s\n", infoLog);
        return false;
    }

    return true;
}

bool ShaderProgram::AddShader(const std::string &path, GLint shaderType)
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
        Logger::err("Error reading shader file: %s\n", e.what());
        return false;
    }

    unsigned int shader = glCreateShader(shaderType);
    char *source = const_cast<char *>(contents.c_str());

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    if (!CheckCompileErrors(shader))
    {
        return false;
    }

    // Create Shader Program
    glAttachShader(m_ID, shader);

    // Cleanup
    glDeleteShader(shader);

    return true;
}
