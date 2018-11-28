#include "TGLMesh.h"

#include <iostream>
#include <string>


GLfloat * calculate_normals(GLfloat * vertices, int length)
{
	GLfloat * out_normals = new GLfloat[length];
	glm::vec3 center(0,0,0);

	for (int i = 0; i < length; i+=3)
	{
		center += glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
		
	}
	center = center * (1.0f / (length / 3));
	for (int i = 0; i < length; i=i+9)
	{
		glm::vec3 vert1 = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
		glm::vec3 vert2 = glm::vec3(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
		glm::vec3 vert3 = glm::vec3(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
		glm::vec3 v1 = vert1 - vert2;
		glm::vec3 v2 = vert1 - vert3;
		glm::vec3 face_center = (vert1 + vert2 + vert3)*(1.0f / 3);
		glm::vec3 out_vec = glm::cross(v1, v2);
		out_vec = glm::normalize(out_vec);
		if (glm::dot(out_vec, face_center - center) < 0)
		{
			out_vec = out_vec*-1.0f;
		}
		out_normals[i] = out_vec[0]; out_normals[i + 1] = out_vec[1]; out_normals[i + 2] = out_vec[2];
		out_normals[i + 3] = out_vec[0]; out_normals[i + 4] = out_vec[1]; out_normals[i + 5] = out_vec[2];
		out_normals[i + 6] = out_vec[0]; out_normals[i + 7] = out_vec[1]; out_normals[i + 8] = out_vec[2];
	}
	/*
	for (int i = 0; i < length; i+=3)
	{
		out_normals[i] = 0.0;
	}
	for (int i = 1; i < length; i+=3)
	{
		out_normals[i] = 0.5;
	}
	for (int i = 2; i < length; i+=3)
	{
		out_normals[i] = 1.0;
	}
	*/
	return out_normals;
}


TGLMesh::TGLMesh(GLfloat * vertices, int in_length)
{
	shader_program = 0;
	draw_flag = true;
	instance_flag = false;
	instance_count = 0;

	length = in_length;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, length*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	vertex_position_attrib = new_attrib();
	glVertexAttribPointer(vertex_position_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(vertex_position_attrib);

	calculate_mesh_normals(vertices, in_length);
}

TGLMesh::TGLMesh(TGLMeshVertices const* in_vertices)
{
	shader_program = 0;
	draw_flag = true;
	instance_flag = false;
	instance_count = 0;
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}
	length = in_vertices->count;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, in_vertices->vertex_VBO);
	vertex_position_attrib = new_attrib();
	glVertexAttribPointer(vertex_position_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(vertex_position_attrib);

	glBindBuffer(GL_ARRAY_BUFFER, in_vertices->normal_VBO);
	vertex_normal_attrib = new_attrib();
	glVertexAttribPointer(vertex_normal_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(vertex_normal_attrib);


	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}
}


TGLMesh::~TGLMesh()
{
}

GLuint TGLMesh::new_attrib()
{
	attribs.push_back(attribs.size());
	return attribs.size() - 1;
}

GLuint TGLMesh::get_VAO()
{
	return VAO;
}

GLuint TGLMesh::get_VBO()
{
	return VBO;
}

std::vector <GLuint> TGLMesh::get_attribs()
{
	return attribs;
}



void TGLMesh::add_shader(TGLShader * in_shader)
{
	shaders.push_back(in_shader);
}

void TGLMesh::set_material(TGLMaterial * in_mat, int uv_index)
{
	material = in_mat;
	
	if (uv_index >= 0)
	{
		uv_attrib = 10;
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, material->get_uv_VBO(uv_index));
		glVertexAttribPointer(uv_attrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(uv_attrib);
	}
}

void TGLMesh::add_texture(TGLTexture * in_texture, GLfloat * in_coords, int coord_length)
{
	
	texture_objects to;
	glBindVertexArray(VAO);
	glGenBuffers(1, &to.VBO);
	//glGenVertexArrays(1, &to.VAO);

	//glBindVertexArray(to.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, to.VBO);

	glBufferData(GL_ARRAY_BUFFER, coord_length * sizeof(GLfloat), in_coords, GL_STATIC_DRAW);
	to.attrib = textures.size() + 10;
	glVertexAttribPointer(to.attrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(to.attrib);
	tex_objects.push_back(to);
	textures.push_back(in_texture);
	glUseProgram(shader_program);
	std::string tex_name = ("texture" + std::to_string(textures.size() - 1)).c_str();
	GLint tex_loc = glGetUniformLocation(shader_program, tex_name.c_str());
	glUniform1i(tex_loc, textures.size() - 1);
}

GLuint TGLMesh::link_shader()
{
	int  success;
	char infoLog[512];

	if (shader_program != 0)
	{
		glDeleteProgram(shader_program);
	}

	shader_program = glCreateProgram();

	for (auto it = shaders.begin(); it != shaders.end(); ++it)
	{
		glAttachShader(shader_program, (*it)->get_shader_name());
	}

	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "SHADER LINK FAILED\n" << infoLog << std::endl;
	}

	return shader_program;
}

TGLMaterial * TGLMesh::get_material()
{
	return material;
}

GLuint TGLMesh::get_shader_program()
{
	return material->get_shader_program();
}

GLuint TGLMesh::get_length()
{
	return length;
}

std::vector <TGLTexture*> TGLMesh::get_textures()
{
	return material->get_textures();
}

void TGLMesh::calculate_mesh_normals(GLfloat * vertices, int in_length)
{
	glBindVertexArray(VAO);
	glGenBuffers(1, &normal_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, normal_VBO);

	GLfloat * normals = calculate_normals(vertices, in_length);

	glBufferData(GL_ARRAY_BUFFER, in_length * sizeof(GLfloat), normals, GL_STATIC_DRAW);
	vertex_normal_attrib = new_attrib();
	glVertexAttribPointer(vertex_normal_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(vertex_normal_attrib);
	delete[] normals;
}

void TGLMesh::enable_instancing(GLfloat * instance_locations, int in_instance_count, int in_unused_count)
{
	instance_flag = true;
	instance_count = in_instance_count;
	buffer_size = instance_count + in_unused_count;

	glBindVertexArray(VAO);
	glGenBuffers(1, &instance_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	
	glBufferData(GL_ARRAY_BUFFER, (instance_count + in_unused_count) * 3 * sizeof(GLfloat), instance_locations, GL_DYNAMIC_DRAW);
	
	instance_attrib = new_attrib();
	glVertexAttribPointer(instance_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(instance_attrib);
	glVertexAttribDivisor(instance_attrib, 1);
	refresh_instances();

}

bool TGLMesh::get_instanced_flag()
{
	return instance_flag;
}

GLuint TGLMesh::get_instance_count()
{
	return instance_count;
}

void TGLMesh::remove_instance(int index)
{
	GLfloat zero[3] = { 0,0,0 };
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	
	//vbo_mem = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	GLfloat * temp_buf = new GLfloat[(instance_count-1) * 3 * sizeof(GLfloat) - index * 3 * sizeof(GLfloat)];
	glGetBufferSubData(GL_ARRAY_BUFFER, (index+1) * 3 * sizeof(GLfloat), (instance_count-1) * 3 * sizeof(GLfloat) - (index) * 3 * sizeof(GLfloat), temp_buf);
	glBufferSubData(GL_ARRAY_BUFFER, (index) * 3 * sizeof(GLfloat), (instance_count-1) * 3 * sizeof(GLfloat) - (index) * 3 * sizeof(GLfloat), temp_buf);

	//glGetBufferSubData(GL_ARRAY_BUFFER, 0, (instance_count - 1) * 3 * sizeof(GLfloat) - (index) * 3 * sizeof(GLfloat), temp_buf);
	//glBufferSubData(GL_ARRAY_BUFFER, (index) * 3 * sizeof(GLfloat), (instance_count - 1) * 3 * sizeof(GLfloat) - (index) * 3 * sizeof(GLfloat), temp_buf);

	//memmove(&vbo_mem[index * 3], &vbo_mem[(index + 1) * 3], instance_count * 3 * sizeof(GLfloat) - index * 3 * sizeof(GLfloat));
	//glUnmapBuffer(GL_ARRAY_BUFFER);
	refresh_instances();
	//glCopyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER, (index + 1) * 3 * sizeof(GLfloat), (index) * 3 * sizeof(GLfloat), instance_count * 3 * sizeof(GLfloat) - index * 3 * sizeof(GLfloat));
	//glBufferSubData(GL_ARRAY_BUFFER, (index)*3*sizeof(GLfloat), 3 * sizeof(GLfloat), zero);
	unused_instances.insert(index);
	instance_count -= 1;
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}
}

int TGLMesh::add_instance(glm::vec3 loc)
{
	GLfloat data[3] = { loc.x,loc.y,loc.z };
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	if (instance_count < buffer_size - 1)
	{
		
		glBufferSubData(GL_ARRAY_BUFFER, instance_count * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), data);
		refresh_instances();
		instance_count += 1;
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			printf("GL ERROR: %d\n", err);
		}
		return instance_count - 1;
	}
	else
	{
		refresh_instances();
		local_vbo_mem.resize((instance_count + 50) * 3, 0.0);
		local_vbo_mem[instance_count * 3] = loc.x;
		local_vbo_mem[instance_count * 3 + 1] = loc.y;
		local_vbo_mem[instance_count * 3 + 2] = loc.z;
		buffer_size = instance_count + 50;
		instance_count += 1;
		glBufferData(GL_ARRAY_BUFFER, (instance_count + 50) * 3 * sizeof(GLfloat), &local_vbo_mem[0], GL_DYNAMIC_DRAW);
		return instance_count - 1;
		printf("TOO MANY INSTANCES\n");
	}
}

std::vector <GLfloat>& TGLMesh::get_instances()
{
	
	return local_vbo_mem;
}

void TGLMesh::refresh_instances()
{
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	local_vbo_mem.resize(instance_count * 3);
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, instance_count * 3 * sizeof(GLfloat), &local_vbo_mem[0]);
}
