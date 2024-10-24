#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <string>

namespace engine
{

class Shader
{
  public:
    Shader()
    {
        id = glCreateProgram();
    }

    unsigned int id;

    void         use()
    {
        glUseProgram(id);
    }

    bool add_shader(const std::string &, unsigned int);

    bool compile();

    void set_bool(const std::string &name, bool val) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)val);
    }

    void set_int(const std::string &name, int val) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), val);
    }
    void set_uint(const std::string &name, int val) const
    {
        glUniform1ui(glGetUniformLocation(id, name.c_str()), val);
    }

    void set_float(const std::string &name, float val) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), val);
    }

    void set_vec2(const std::string &name, const glm::vec2 &vec) const
    {
        glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &vec[0]);
    }

    void set_vec3(const std::string &name, const glm::vec3 &vec) const
    {
        glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &vec[0]);
    }

    void set_vec4(const std::string &name, const glm::vec4 &vec) const
    {
        glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &vec[0]);
    }

    void set_mat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void set_mat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void set_mat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

  private:
    bool check_compile_errors(unsigned int);
};

} // namespace engine