#include "engine/mesh/obj/material.hpp"
#include "engine/shader_program/shader_program.hpp"
#include <cstdio>
#include <engine/mesh/obj/obj.hpp>
#include <filesystem>
#include <fstream>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

using namespace engine;

bool load_obj(const std::basic_string<char> &obj_path, std::vector<mesh::vertex> &vertices, std::vector<mesh::uv> &uvs,
              std::vector<mesh::normal> &normals, std::vector<mesh::face_indices> &faces, mesh::material &material)
{
    std::ifstream obj_file(obj_path);
    std::string line;

    if (!obj_file.is_open())
    {
        return false;
    }

    while (std::getline(obj_file, line))
    {
        std::stringstream ss(line);
        std::string token;
        ss >> token;

        if (token == "v")
        {
            mesh::vertex v;
            ss >> v.x;
            ss >> v.y;
            ss >> v.z;
            vertices.push_back(v);
        }
        else if (token == "vt")
        {
            mesh::uv uv;
            ss >> uv.x;
            ss >> uv.y;
            uvs.push_back(uv);
        }
        else if (token == "vn")
        {
            mesh::normal n;
            ss >> n.x;
            ss >> n.y;
            ss >> n.z;
            normals.push_back(n);
        }
        else if (token == "f")
        {
            mesh::face_indices f;
            std::string v1, v2, v3;
            ss >> v1;
            ss >> v2;
            ss >> v3;

            sscanf(v1.c_str(), "%u/%u/%u", &f.v0.vertex_index, &f.v0.uv_index, &f.v0.normal_index);
            sscanf(v2.c_str(), "%u/%u/%u", &f.v1.vertex_index, &f.v1.uv_index, &f.v1.normal_index);
            sscanf(v3.c_str(), "%u/%u/%u", &f.v2.vertex_index, &f.v2.uv_index, &f.v2.normal_index);

            f.v0.vertex_index--;
            f.v1.vertex_index--;
            f.v2.vertex_index--;

            f.v0.uv_index--;
            f.v1.uv_index--;
            f.v2.uv_index--;

            f.v0.normal_index--;
            f.v1.normal_index--;
            f.v2.normal_index--;

            faces.push_back(f);
        }
        else if (token == "mtllib")
        {
            std::string mtl_filename;
            std::filesystem::path obj_parent_dir(obj_path);
            obj_parent_dir = obj_parent_dir.parent_path();

            ss >> mtl_filename;

            std::filesystem::path mtl_path(obj_parent_dir.append(mtl_filename));

            if (!material.load_mtl(mtl_path))
            {
                throw std::runtime_error("Error loading mtl file: " + obj_path);
            }
        }
    }

    return true;
}

void process_faces(std::vector<mesh::index> &indices, std::vector<mesh::point> &points, const std::vector<mesh::vertex> &vertices,
                   const std::vector<mesh::uv> &uvs, const std::vector<mesh::normal> &normals, const std::vector<mesh::face_indices> &faces)
{
    std::unordered_map<mesh::point_indices, mesh::index, mesh::point_indices_hash> temp_points;

    for (auto f_indices : faces)
    {
        mesh::point p0{vertices[f_indices.v0.vertex_index].x, vertices[f_indices.v0.vertex_index].y, vertices[f_indices.v0.vertex_index].z,
                       uvs[f_indices.v0.uv_index].x,          uvs[f_indices.v0.uv_index].y,          normals[f_indices.v0.normal_index].x,
                       normals[f_indices.v0.normal_index].y,  normals[f_indices.v0.normal_index].z};
        mesh::point p1{vertices[f_indices.v1.vertex_index].x, vertices[f_indices.v1.vertex_index].y, vertices[f_indices.v1.vertex_index].z,
                       uvs[f_indices.v1.uv_index].x,          uvs[f_indices.v1.uv_index].y,          normals[f_indices.v1.normal_index].x,
                       normals[f_indices.v1.normal_index].y,  normals[f_indices.v1.normal_index].z};
        mesh::point p2{vertices[f_indices.v2.vertex_index].x, vertices[f_indices.v2.vertex_index].y, vertices[f_indices.v2.vertex_index].z,
                       uvs[f_indices.v2.uv_index].x,          uvs[f_indices.v2.uv_index].y,          normals[f_indices.v2.normal_index].x,
                       normals[f_indices.v2.normal_index].y,  normals[f_indices.v2.normal_index].z};

        auto it0 = temp_points.find({f_indices.v0.vertex_index, f_indices.v0.uv_index, f_indices.v0.normal_index});
        auto it1 = temp_points.find({f_indices.v1.vertex_index, f_indices.v1.uv_index, f_indices.v1.normal_index});
        auto it2 = temp_points.find({f_indices.v2.vertex_index, f_indices.v2.uv_index, f_indices.v2.normal_index});

        if (it0 != temp_points.end()) // point 0 in map, just reference existing point
        {
            indices.push_back(it0->second);
        }
        else // point not in map, add it and push back point
        {
            auto idx = points.size();
            mesh::point_indices pi{f_indices.v0.vertex_index, f_indices.v0.uv_index, f_indices.v0.normal_index};
            temp_points[pi] = idx;
            points.push_back(p0);
            indices.push_back(idx);
        }

        if (it1 != temp_points.end()) // point 1 in map, just reference existing point
        {
            indices.push_back(it1->second);
        }
        else // point not in map, add it and push back point
        {
            auto idx = points.size();
            mesh::point_indices pi{f_indices.v1.vertex_index, f_indices.v1.uv_index, f_indices.v1.normal_index};
            temp_points[pi] = points.size();
            points.push_back(p1);
            indices.push_back(idx);
        }

        if (it2 != temp_points.end()) // point 2 in map, just reference existing point
        {
            indices.push_back(it2->second);
        }
        else // point not in map, add it and push back point
        {
            auto idx = points.size();
            mesh::point_indices pi{f_indices.v2.vertex_index, f_indices.v2.uv_index, f_indices.v2.normal_index};
            temp_points[pi] = points.size();
            points.push_back(p2);
            indices.push_back(idx);
        }
    }
}

mesh::obj::obj(const std::basic_string<char> &name, const std::basic_string<char> &obj_path) : mesh_t(name)
{
    std::vector<vertex> vertices;
    std::vector<uv> uvs;
    std::vector<normal> normals;
    std::vector<face_indices> faces;

    engine::shader vertex_shader("resources/shaders/obj/obj.vs", GL_VERTEX_SHADER);
    engine::shader fragment_shader("resources/shaders/obj/obj.fs", GL_FRAGMENT_SHADER);

    engine::shader texture_vertex_shader("resources/shaders/obj/obj_texture.vs", GL_VERTEX_SHADER);
    engine::shader texture_fragment_shader("resources/shaders/obj/obj_texture.fs", GL_FRAGMENT_SHADER);

    if (!load_obj(obj_path, vertices, uvs, normals, faces, m_material))
    {
        throw std::runtime_error("Error opening obj file: " + obj_path);
    }

    process_faces(m_indices, m_points, vertices, uvs, normals, faces);

    for (auto &[mat_name, attributes] : m_material.m_materials)
    {
        std::cout << "OBJ file loaded material: " << mat_name << std::endl;
    }

    m_shader_program.add_shader(vertex_shader.id());
    m_shader_program.add_shader(fragment_shader.id());
    m_shader_program.link();

    m_texture_shader_program.add_shader(texture_vertex_shader.id());
    m_texture_shader_program.add_shader(texture_fragment_shader.id());
    m_texture_shader_program.link();

    m_vao.bind();
    m_vbo.bind();
    m_ebo.bind();

    m_vao.set(0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);                   // pos
    m_vao.set(1, 2, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float))); // uv
    m_vao.set(2, 3, GL_FLOAT, 8 * sizeof(float), (void *)(5 * sizeof(float))); // normal

    m_vbo.init(&m_points[0], (m_points.size() * sizeof(mesh::point)), GL_DYNAMIC_DRAW);
    m_ebo.init(&m_indices[0], (m_indices.size() * sizeof(mesh::index)), GL_DYNAMIC_DRAW);

    m_ebo.unbind();
    m_vao.unbind();
    m_vbo.unbind();
}

void mesh::obj::update(double dt)
{
    m_model = glm::translate(glm::mat4(1), m_pos);
}

void mesh::obj::draw(const glm::mat4 &model, const glm::mat4 &projection, const glm::mat4 &view)
{

    m_vbo.bind();
    m_vao.bind();
    m_ebo.bind();

    assert(m_material.m_materials.begin() != m_material.m_materials.end());
    auto &[material_name, material_attributes] = *m_material.m_materials.begin();

    shader_program &shader_program = m_shader_program;

    if (material_attributes.m_texture)
    {
        shader_program = m_texture_shader_program;
        material_attributes.m_texture->bind();
    }

    shader_program.bind();
    shader_program.set_mat4("model", model * m_model);
    shader_program.set_mat4("view", view);
    shader_program.set_mat4("projection", projection);

    glDrawElements(GL_TRIANGLES,     // mode
                   m_indices.size(), // count
                   GL_UNSIGNED_INT,  // type
                   (void *)0         // element array buffer offset
    );

    EBO::unbind();
    VAO::unbind();
    VBO::unbind();
    texture::unbind();
    shader_program::unbind();
    mesh_t::draw(model, view, projection);
}
