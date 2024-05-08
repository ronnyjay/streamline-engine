#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <string>

namespace engine
{

class Shader
{
  public:
    Shader(const std::basic_string<char> &, GLenum);

    void use();

    // utility uniform functions
    void set_bool(const std::string &, bool) const;
    void set_int(const std::string &, int) const;
    void set_unsigned_int(const std::string &, int) const;
    void set_float(const std::string &, float) const;
    void set_vec2(const std::string &, const glm::vec2 &) const;
    void set_vec2(const std::string &, float, float) const;
    void set_vec3(const std::string &, const glm::vec3 &) const;
    void set_vec3(const std::string &, float, float, float) const;
    void set_vec4(const std::string &, const glm::vec4 &) const;
    void set_vec4(const std::string &, float, float, float, float);
    void set_mat2(const std::string &, const glm::mat2 &) const;
    void set_mat3(const std::string &, const glm::mat3 &) const;
    void set_mat4(const std::string &, const glm::mat4 &) const;

    GLuint get_id() const;

    static GLuint load(const std::basic_string<char> &, GLenum);

    ~Shader();

  private:
    GLuint m_id;
};

class ShaderProgram
{
  public:
    ShaderProgram();

    void add_shader(GLuint);

    void bind();
    void unbind();

    void link();

    // utility uniform functions
    void set_bool(const std::string &, bool) const;
    void set_int(const std::string &, int) const;
    void set_unsigned_int(const std::string &, int) const;
    void set_float(const std::string &, float) const;
    void set_vec2(const std::string &, const glm::vec2 &) const;
    void set_vec2(const std::string &, float, float) const;
    void set_vec3(const std::string &, const glm::vec3 &) const;
    void set_vec3(const std::string &, float, float, float) const;
    void set_vec4(const std::string &, const glm::vec4 &) const;
    void set_vec4(const std::string &, float, float, float, float);
    void set_mat2(const std::string &, const glm::mat2 &) const;
    void set_mat3(const std::string &, const glm::mat3 &) const;
    void set_mat4(const std::string &, const glm::mat4 &) const;

    GLuint get_id() const;

  private:
    GLuint m_id;
};

}; // namespace engine