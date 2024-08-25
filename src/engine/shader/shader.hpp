#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "libstreamline/debug/logger.hpp"

#include <string>

namespace engine
{

class shader_program
{
  public:
    static constexpr size_t MAX_NUM_LIGHTS = 10;

    shader_program()
        : m_log("shader_program")
    {
        m_ID = glCreateProgram();
    }

    operator unsigned int() const
    {
        return m_ID;
    }

    void bind()
    {
        glUseProgram(m_ID);
    }

    void unbind()
    {
        glUseProgram(0);
    }

    bool add_shader(const std::string &path, GLint type);

    bool compile();

    void set_bool(const std::string &, bool) const;
    void set_int(const std::string &, int) const;
    void set_uint(const std::string &, int) const;
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

  private:
    unsigned int m_ID;
    logger m_log;

    bool check_compile_errors(unsigned int);
};

} // namespace engine
