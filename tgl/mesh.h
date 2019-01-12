#pragma once
#ifndef TGL_MESH_H_
#define TGL_MESH_H_

#include <set>
#include <vector>

#include "tgl/tgl_gl.h"
#include "tgl/component.h"
#include "tgl/material.h"
#include "tgl/mesh_vertices.h"
#include "tgl/shader.h"
#include "tgl/texture.h"
#include "tmc/block_generator.h"

namespace tgl
{

struct texture_objects
{
    GLuint VBO;
    GLuint attrib;
};

class Mesh : public tgl::Component
{
    GLuint VAO;
    GLuint VBO;
    GLuint normal_VBO;
    GLuint instance_VBO;
    GLuint light_VBO;
    GLuint shader_program;

    bool instance_flag;
    bool light_data_enabled;
    GLuint instance_count;
    GLuint buffer_size;
    GLfloat * vbo_mem;

    GLuint vertex_position_attrib;
    GLuint vertex_normal_attrib;
    GLuint uv_attrib;
    GLuint instance_attrib;
    GLuint light_attrib;
    std::vector <GLuint> attribs;
    std::vector <tgl::Shader *> shaders;
    std::vector <tgl::Texture *> textures;
    std::vector <texture_objects> tex_objects;
    std::set <int> unused_instances;
    tgl::Material * material;

    GLuint length;

    GLuint new_attrib();

 public:
    std::vector <GLfloat> local_vbo_mem;

    std::vector <unsigned char> local_light_mem;
    std::vector <GLfloat> local_light_mem_vec;
    int refreshes;

    Mesh(GLfloat * vertices, int length);
    explicit Mesh(MeshVertices const* in_vertices);
    ~Mesh();
    GLuint get_VAO();
    GLuint get_VBO();
    std::vector <GLuint> get_attribs();
    void add_shader(tgl::Shader * in_shader);
    void set_material(tgl::Material * in_mat, int uv_index = -1);
    void add_texture(tgl::Texture * in_texture,
                     GLfloat * in_coords,
                     int coord_length);
    GLuint link_shader();
    tgl::Material * get_material();
    GLuint get_shader_program();
    GLuint get_length();
    std::vector <tgl::Texture*> get_textures();
    void calculate_mesh_normals(GLfloat * vertices, int in_length);
    void enable_instancing(GLfloat * instance_locations,
                           int in_length,
                           int in_unused_count = 0);
    bool get_instanced_flag();
    GLuint get_instance_count();
    void remove_instance(int index);
    int add_instance(glm::vec3 loc);
    std::vector <GLfloat>& get_instances();
    void refresh_instances();
    void enable_light_data(int unused);
    void refresh_light_data(std::vector <unsigned char>& in_data);
    void refresh_light_data_vec(std::vector <GLfloat>& in_data);
};

}  // namespace tgl

#endif  // TGL_MESH_H_
