#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <string_view>

namespace engine
{

// clang-format off
enum class texture_format { NONE, RED, RGB, RGBA };
enum class texture_type   { NONE, DIFFUSE, SPECULAR, NORMAL, HEIGHT };
// clang-format on

struct texture
{
    texture(const std::string_view path);

    texture_format format;
    texture_type   type;

    int width;
    int height;

    void bind(uint32_t slot = 0)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    void unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

  private:
    uint32_t ID;
};

} // namespace engine