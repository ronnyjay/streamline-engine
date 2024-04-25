#include <engine/shader/shader.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace engine;

GLuint shader::load_shader(const std::basic_string<char> &filepath, GLenum shader_type)
{
    GLuint shader_id = glCreateShader(shader_type);

    // Read file
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening shader file: " + filepath);
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
    const GLchar *contents_p = file_contents.c_str();
    glShaderSource(shader_id, 1, &contents_p, NULL);
    glCompileShader(shader_id);

    // Check shader
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &logLength);
    std::string shaderCompileError;

    if (logLength)
    {
        shaderCompileError.resize(logLength);
        glGetShaderInfoLog(shader_id, logLength, NULL, &shaderCompileError[0]);
    }

    if (result != GL_TRUE)
    {
        std::string error = "Error compiling shader: ";
        error += filepath + " - ";
        error += shaderCompileError;

        throw std::runtime_error(error + shaderCompileError);
    }

    return shader_id;
}

shader::shader(const std::basic_string<char> &filepath, GLenum shader_type)
{
    m_id = load_shader(filepath, shader_type);
}

void shader::use()
{
    glUseProgram(m_id);
}

// utility uniform functions
void shader::set_bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void shader::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void shader::set_uint(const std::string &name, int value) const
{
    glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
}

void shader::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void shader::set_vec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
void shader::set_vec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}

void shader::set_vec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
void shader::set_vec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

void shader::set_vec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void shader::set_vec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

void shader::set_mat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void shader::set_mat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void shader::set_mat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

GLuint shader::id() const
{
    return m_id;
}

shader::~shader()
{
    glDeleteShader(m_id);
}
