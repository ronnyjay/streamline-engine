#pragma once

#include <engine/stb/stb_image.hpp>

#include <filesystem>
#include <glad/gl.h>

#include <string>

namespace engine
{

class texture
{
  public:
    texture(const std::filesystem::path &image_path);

    void bind();
    static void unbind();

    GLuint get_id() const;

    ~texture();

    int m_width;
    int m_height;
    int m_channels;

  private:
    GLuint m_id;
};

}; // namespace engine