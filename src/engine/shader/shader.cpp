#include <engine/shader/shader.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace engine;

Shader::Shader(const std::basic_string<char> &filePath, GLenum shaderType)
{
    m_id = load(filePath, shaderType);
}

void Shader::use()
{
    glUseProgram(m_id);
}

void Shader::set_bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_unsigned_int(const std::string &name, int value) const
{
    glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_vec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}

void Shader::set_vec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

void Shader::set_vec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

void Shader::set_mat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

GLuint Shader::get_id() const
{
    return m_id;
}

GLuint Shader::load(const std::basic_string<char> &filePath, GLenum shaderType)
{
    GLuint shader_id = glCreateShader(shaderType);

    // Read file
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening shader file: " + filePath);
    }

    std::string file_contents;
    {
        std::stringstream stream;
        stream << file.rdbuf();
        file_contents = stream.str();
    }

    GLint result = GL_FALSE;
    GLint logLength;

    // Compile shader
    const GLchar *contentsPtr = file_contents.c_str();
    glShaderSource(shader_id, 1, &contentsPtr, NULL);
    glCompileShader(shader_id);

    // Check shader
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &logLength);
    std::string shader_compile_error;

    if (logLength)
    {
        shader_compile_error.resize(logLength);
        glGetShaderInfoLog(shader_id, logLength, NULL, &shader_compile_error[0]);
    }

    if (result != GL_TRUE)
    {
        std::string error = "Error compiling shader: ";
        error += filePath + " - ";
        error += shader_compile_error;

        throw std::runtime_error(error + shader_compile_error);
    }

    return shader_id;
}

Shader::~Shader()
{
    glDeleteShader(m_id);
}

ShaderProgram::ShaderProgram()
{
    m_id = glCreateProgram();
}

void ShaderProgram::add_shader(GLuint shaderId)
{
    glAttachShader(m_id, shaderId);
}

void ShaderProgram::bind()
{
    glUseProgram(m_id);
}

void ShaderProgram::unbind()
{
    glUseProgram(0);
}

void ShaderProgram::link()
{
    GLint result = GL_FALSE;
    GLint log_length;
    std::string program_link_error;

    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &result);
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length)
    {
        program_link_error.resize(log_length);
        glGetProgramInfoLog(m_id, log_length, NULL, &program_link_error[0]);
    }

    if (result != GL_TRUE)
    {
        std::string error = "Error compiling shader: ";
        error += program_link_error;

        throw std::runtime_error(error + program_link_error);
    }
}

void ShaderProgram::set_bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void ShaderProgram::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::set_unsigned_int(const std::string &name, int value) const
{
    glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::set_vec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void ShaderProgram::set_vec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}

void ShaderProgram::set_vec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void ShaderProgram::set_vec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

void ShaderProgram::set_vec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void ShaderProgram::set_vec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

void ShaderProgram::set_mat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::set_mat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::set_mat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

GLuint ShaderProgram::get_id() const
{
    return m_id;
}