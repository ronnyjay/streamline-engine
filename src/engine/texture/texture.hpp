#pragma once

#include <glad/gl.h>

namespace engine
{

class Texture2D
{
  public:
    Texture2D(const char *file);

    void Bind();
    void Unbind();

    int Width() const;
    int Height() const;
    int Channels() const;

    unsigned int Id() const;

  private:
    int m_Width;
    int m_Height;
    int m_Channels;
    unsigned int m_Id;
};

}; // namespace engine