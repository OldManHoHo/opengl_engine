#include "tgl/Mesh.h"

#include <iostream>
#include <string>

namespace tgl
{

GLfloat * calculate_normals(GLfloat * vertices, int length)
{
	
	glm::vec3 center(0,0,0);

	for (int i = 0; i < length; i+=3)
	{
		center += glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
		
	}
	center = center * (1.0f / (length / 3));
	GLfloat * out_normals = new GLfloat[length];
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


Mesh::Mesh(GLfloat * vertices, int in_length)
{
	shader_program = 0;
	draw_flag = true;
	instance_flag = false;
	instance_count = 0;
	light_data_enabled = false;

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

	refreshes = 0;
}

Mesh::Mesh(MeshVertices const* in_vertices)
{
	shader_program = 0;
	draw_flag = true;
	instance_flag = false;
	instance_count = 0;
	light_data_enabled = false;
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


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &normal_VBO);
	glDeleteBuffers(1, &instance_VBO);
}

GLuint Mesh::new_attrib()
{
	attribs.push_back(attribs.size());
	return attribs.size() - 1;
}

GLuint Mesh::get_VAO()
{
	return VAO;
}

GLuint Mesh::get_VBO()
{
	return VBO;
}

std::vector <GLuint> Mesh::get_attribs()
{
	return attribs;
}



void Mesh::add_shader(tgl::Shader * in_shader)
{
	shaders.push_back(in_shader);
}

void Mesh::set_material(tgl::Material * in_mat, int uv_index)
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

void Mesh::add_texture(tgl::Texture * in_texture, GLfloat * in_coords, int coord_length)
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

GLuint Mesh::link_shader()
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

tgl::Material * Mesh::get_material()
{
	return material;
}

GLuint Mesh::get_shader_program()
{
	return material->get_shader_program();
}

GLuint Mesh::get_length()
{
	return length;
}

std::vector <tgl::Texture*> Mesh::get_textures()
{
	return material->get_textures();
}

void Mesh::calculate_mesh_normals(GLfloat * vertices, int in_length)
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

void Mesh::enable_instancing(GLfloat * instance_locations, int in_instance_count, int in_unused_count)
{
	int err;
	instance_flag = true;
	instance_count = in_instance_count;
	buffer_size = instance_count + in_unused_count;

	glBindVertexArray(VAO);
	glGenBuffers(1, &instance_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	
	glBufferData(GL_ARRAY_BUFFER, (instance_count + in_unused_count) * 3 * sizeof(GLfloat), instance_locations, GL_DYNAMIC_DRAW);
	
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}

	instance_attrib = new_attrib();
	glVertexAttribPointer(instance_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(instance_attrib);
	glVertexAttribDivisor(instance_attrib, 1);
	refresh_instances();

	enable_light_data(in_unused_count);
}

bool Mesh::get_instanced_flag()
{
	return instance_flag;
}

GLuint Mesh::get_instance_count()
{
	return instance_count;
}

void Mesh::remove_instance(int index)
{
	GLfloat zero[3] = { 0,0,0 };
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	
	//vbo_mem = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	GLfloat * temp_buf = new GLfloat[(instance_count-1) * 3 * sizeof(GLfloat) - index * 3 * sizeof(GLfloat)];
	glGetBufferSubData(GL_ARRAY_BUFFER, (index+1) * 3 * sizeof(GLfloat), (instance_count-1) * 3 * sizeof(GLfloat) - (index) * 3 * sizeof(GLfloat), temp_buf);
	glBufferSubData(GL_ARRAY_BUFFER, (index) * 3 * sizeof(GLfloat), (instance_count-1) * 3 * sizeof(GLfloat) - (index) * 3 * sizeof(GLfloat), temp_buf);
	delete[] temp_buf;
	//glGetBufferSubData(GL_ARRAY_BUFFER, 0, (instance_count - 1) * 3 * sizeof(GLfloat) - (index) * 3 * sizeof(GLfloat), temp_buf);
	//glBufferSubData(GL_ARRAY_BUFFER, (index) * 3 * sizeof(GLfloat), (instance_count - 1) * 3 * sizeof(GLfloat) - (index) * 3 * sizeof(GLfloat), temp_buf);

	//memmove(&vbo_mem[index * 3], &vbo_mem[(index + 1) * 3], instance_count * 3 * sizeof(GLfloat) - index * 3 * sizeof(GLfloat));
	//glUnmapBuffer(GL_ARRAY_BUFFER);
	refresh_instances();

	if (light_data_enabled)
	{
		glBindBuffer(GL_ARRAY_BUFFER, light_VBO);
		unsigned char * temp_c = new unsigned char[(instance_count - 1) * sizeof(GLbyte) - index * sizeof(GLbyte)];
		glGetBufferSubData(GL_ARRAY_BUFFER, (index + 1) * sizeof(GLbyte), (instance_count - 1) * sizeof(GLbyte) - (index) * sizeof(GLbyte), temp_c);
		glBufferSubData(GL_ARRAY_BUFFER, (index) * sizeof(GLbyte), (instance_count - 1) * sizeof(GLbyte) - (index) * sizeof(GLbyte), temp_c);
		delete[] temp_c;
	}

	//glCopyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER, (index + 1) * 3 * sizeof(GLfloat), (index) * 3 * sizeof(GLfloat), instance_count * 3 * sizeof(GLfloat) - index * 3 * sizeof(GLfloat));
	//glBufferSubData(GL_ARRAY_BUFFER, (index)*3*sizeof(GLfloat), 3 * sizeof(GLfloat), zero);
	//unused_instances.insert(index);
	instance_count -= 1;
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}
}

int Mesh::add_instance(glm::vec3 loc)
{
	GLenum err;
	GLfloat data[3] = { loc.x,loc.y,loc.z };
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	if (instance_count < buffer_size - 1)
	{
		glBufferSubData(GL_ARRAY_BUFFER, instance_count * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), data);
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			printf("GL ERROR: %d\n", err);
		}
		instance_count += 1;
		refresh_instances();
		unsigned char c_data[1] = { 128 };
		if (light_data_enabled)
		{
			glBindBuffer(GL_ARRAY_BUFFER, light_VBO);
			while ((err = glGetError()) != GL_NO_ERROR)
			{
				printf("GL ERROR: %d\n", err);
			}
			glBufferSubData(GL_ARRAY_BUFFER, instance_count*sizeof(GLbyte), sizeof(GLbyte), c_data);
		}

		
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
		refresh_instances();

		if (light_data_enabled)
		{
			glBindBuffer(GL_ARRAY_BUFFER, light_VBO);
			local_light_mem.resize((instance_count + 50), 128);
			local_light_mem[instance_count] = 128;
			buffer_size = instance_count + 50;
			glBufferData(GL_ARRAY_BUFFER, (instance_count - 1 + 50) * sizeof(GLbyte), &local_light_mem[0], GL_DYNAMIC_DRAW);
		}

		return instance_count - 1;
		printf("TOO MANY INSTANCES\n");
	}
}

std::vector <GLfloat>& Mesh::get_instances()
{
	
	return local_vbo_mem;
}

void Mesh::refresh_instances()
{
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	local_vbo_mem.resize(instance_count * 3);
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, instance_count * 3 * sizeof(GLfloat), &local_vbo_mem[0]);
}

void Mesh::enable_light_data(int unused)
{
	if (0)
	{
		light_data_enabled = true;
		glBindVertexArray(VAO);
		glGenBuffers(1, &light_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, light_VBO);

		std::vector<GLbyte> zeroes(instance_count + unused, 128);

		glBufferData(GL_ARRAY_BUFFER, (instance_count + unused) * sizeof(GLbyte), &zeroes[0], GL_DYNAMIC_DRAW);

		light_attrib = new_attrib();
		glVertexAttribPointer(light_attrib, 1, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(GLbyte), (void*)0);
		glEnableVertexAttribArray(light_attrib);
		glVertexAttribDivisor(light_attrib, 1);
		refresh_instances();
	}
	else
	{
		light_data_enabled = true;
		glBindVertexArray(VAO);
		glGenBuffers(1, &light_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, light_VBO);

		std::vector<GLfloat> zeroes((instance_count + unused)*3, 0.0);

		glBufferData(GL_ARRAY_BUFFER, (instance_count + unused)*3 * sizeof(GLfloat), &zeroes[0], GL_DYNAMIC_DRAW);

		light_attrib = new_attrib();
		glVertexAttribPointer(light_attrib, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(light_attrib);
		glVertexAttribDivisor(light_attrib, 1);
		refresh_instances();
	}
}

void Mesh::refresh_light_data(std::vector <unsigned char>& in_data)
{
	if (local_vbo_mem.size())
	{
		glBindVertexArray(VAO);
		int err;
		glBindBuffer(GL_ARRAY_BUFFER, light_VBO);
		//std::vector<GLfloat> zeroes(local_vbo_mem.size()/3, 0);
		local_light_mem.resize(instance_count);
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, instance_count * sizeof(GLbyte), &local_light_mem[0]);
		if (1)
		{
			for (int i = 0; i < local_light_mem.size(); ++i)
			{
				in_data[i] = (local_light_mem[i] + in_data[i]) / (2);
			}
		}
		glBufferData(GL_ARRAY_BUFFER, (local_vbo_mem.size()/3) * sizeof(GLbyte), &in_data[0], GL_DYNAMIC_DRAW);
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			printf("GL ERROR: %d\n", err);
		}
		refresh_instances();
		refreshes += 1;
	}
}

void Mesh::refresh_light_data_vec(std::vector <GLfloat>& in_data)
{
	if (local_vbo_mem.size())
	{
		glBindVertexArray(VAO);
		int err;
		glBindBuffer(GL_ARRAY_BUFFER, light_VBO);
		//std::vector<GLfloat> zeroes(local_vbo_mem.size()/3, 0);
		local_light_mem_vec.resize(instance_count*3);
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, instance_count*3 *sizeof(GLfloat), &local_light_mem_vec[0]);
		if (1)
		{
			for (int i = 0; i < local_light_mem_vec.size(); ++i)
			{
				in_data[i] = (local_light_mem_vec[i] + in_data[i])*0.5f;
			}
		}
		glBufferData(GL_ARRAY_BUFFER, (local_vbo_mem.size()) * sizeof(GLfloat), &in_data[0], GL_DYNAMIC_DRAW);
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			printf("GL ERROR: %d\n", err);
		}
 		refresh_instances();
		refreshes += 1;
	}
}

} // namespace tgl
