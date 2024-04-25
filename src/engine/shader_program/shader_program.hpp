#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <string>

namespace engine
{

class shader_program
{
  public:
    shader_program();

    void add_shader(GLuint shader_id);

    void bind();
    static void unbind();

    void link();

    // utility uniform functions
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_uint(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;

    void set_vec2(const std::string &name, const glm::vec2 &value) const;
    void set_vec2(const std::string &name, float x, float y) const;

    void set_vec3(const std::string &name, const glm::vec3 &value) const;
    void set_vec3(const std::string &name, float x, float y, float z) const;

    void set_vec4(const std::string &name, const glm::vec4 &value) const;
    void set_vec4(const std::string &name, float x, float y, float z, float w);

    void set_mat2(const std::string &name, const glm::mat2 &mat) const;
    void set_mat3(const std::string &name, const glm::mat3 &mat) const;
    void set_mat4(const std::string &name, const glm::mat4 &mat) const;

    GLuint id() const;

  private:
    GLuint m_id;
};

}; // namespace engine
