#pragma once
#ifndef _TGL_MESH
#define _TGL_MESH


#include "tgl_gl.h"

#include <vector>
#include <set>

#include "TGLShader.h"
#include "TGLComponent.h"
#include "TGLTexture.h"
#include "TGLMeshVertices.h"
#include "TGLMaterial.h"
#include "BlockGenerator.h"

struct texture_objects
{
	GLuint VBO;
	GLuint attrib;
};

class TGLMesh : public TGLComponent
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
	std::vector <TGLShader *> shaders;
	std::vector <TGLTexture *> textures;
	std::vector <texture_objects> tex_objects;
	std::set <int> unused_instances;
	TGLMaterial * material;

	GLuint length;

	GLuint new_attrib();

public:
	std::vector <GLfloat> local_vbo_mem;

	std::vector <unsigned char> local_light_mem;
	int refreshes;

	TGLMesh(GLfloat * vertices, int length);
	TGLMesh(TGLMeshVertices const* in_vertices);
	~TGLMesh();
	GLuint get_VAO();
	GLuint get_VBO();
	std::vector <GLuint> get_attribs();
	void add_shader(TGLShader * in_shader);
	void set_material(TGLMaterial * in_mat, int uv_index = -1);
	void add_texture(TGLTexture * in_texture, GLfloat * in_coords, int coord_length);
	GLuint link_shader();
	TGLMaterial * get_material();
	GLuint get_shader_program();
	GLuint get_length();
	std::vector <TGLTexture*> get_textures();
	void calculate_mesh_normals(GLfloat * vertices, int in_length);
	void enable_instancing(GLfloat * instance_locations, int in_length, int in_unused_count = 0);
	bool get_instanced_flag();
	GLuint get_instance_count();
	void remove_instance(int index);
	int add_instance(glm::vec3 loc);
	std::vector <GLfloat>& get_instances();
	void refresh_instances();
	
	void enable_light_data(int unused);
	void refresh_light_data(std::vector <unsigned char>& in_data);
};

#endif
