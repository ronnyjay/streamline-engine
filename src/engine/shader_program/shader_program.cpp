#include <engine/shader_program/shader_program.hpp>

#include <stdexcept>

using namespace engine;

shader_program::shader_program()
{
    m_id = glCreateProgram();
}

void shader_program::add_shader(GLuint shader_id)
{
    glAttachShader(m_id, shader_id);
}

void shader_program::bind()
{
    glUseProgram(m_id);
}

void shader_program::unbind()
{
    glUseProgram(0);
}

void shader_program::link()
{
    GLint result = GL_FALSE;
    GLint logLength;
    std::string programLinkError;

    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &result);
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength)
    {
        programLinkError.resize(logLength);
        glGetProgramInfoLog(m_id, logLength, NULL, &programLinkError[0]);
    }

    if (result != GL_TRUE)
    {
        std::string error = "Error compiling shader: ";
        error += programLinkError;

        throw std::runtime_error(error + programLinkError);
    }
}

// utility uniform functions
void shader_program::set_bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void shader_program::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void shader_program::set_uint(const std::string &name, int value) const
{
    glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
}

void shader_program::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void shader_program::set_vec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
void shader_program::set_vec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}

void shader_program::set_vec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}
void shader_program::set_vec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

void shader_program::set_vec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void shader_program::set_vec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

void shader_program::set_mat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void shader_program::set_mat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void shader_program::set_mat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

GLuint shader_program::id() const
{
    return m_id;
}