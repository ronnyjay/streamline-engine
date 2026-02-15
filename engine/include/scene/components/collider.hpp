#pragma once

#include <glad/gl.h>

#include <array>

#include <math/vec3.hpp>

namespace engine
{

struct Cuboid
{
    friend class CuboidRenderer;

    Cuboid(float x, float y, float z)
    {
        // clang-format off
       vertices = {
            vec3{-x, -y, -z},
            vec3{+x, -y, -z},
            vec3{-x, +y, -z},
            vec3{+x, +y, -z},
            vec3{-x, -y, +z},
            vec3{+x, -y, +z},
            vec3{-x, +y, +z},
            vec3{+x, +y, +z},
        };
        // clang-format on
    }

  private:
    std::array<vec3, 8> vertices;
};

struct CuboidRenderer
{
    CuboidRenderer()
    {
        glGenVertexArrays(1, &vao);

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void *)0);

        glBindVertexArray(0);
    }

    ~CuboidRenderer()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }

    void setData(Cuboid const &cuboid)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, BUFFER_SIZE, &cuboid.vertices);
    }

    void draw()
    {
        glBindVertexArray(vao);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    }

  private:
    GLuint                  vao;
    GLuint                  vbo;
    GLuint                  ebo;

    static constexpr GLuint BUFFER_SIZE = 8 * sizeof(vec3);

    // clang-format off
    static constexpr GLuint INDICES[24] = {
        0, 1, 1, 3, 3, 2, 2, 0,
        4, 5, 5, 7, 7, 6, 6, 4,
        0, 4, 1, 5, 2, 6, 3, 7};
    // clang-format on
};

struct Collider
{
    static Cuboid cuboid(float x, float y, float z)
    {
        return Cuboid(x, y, z);
    }
};

} // namespace engine
