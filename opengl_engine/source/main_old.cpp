#pragma once

#include "tgl_gl.h"
#include <iostream>

#include "TGLBase.h"
#include "TGLCamera.h"
#include "TGLPlayer.h"
#include "TGLChunkSpawn.h"


GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f,  -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f,  -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f,  -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f,  -0.5f, 0.5f,
};

GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, //face 1, (-1,0,0)
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 
	1.0f, 1.0f,-1.0f, //face 2 upper (0,0,-1)
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,//face 3 (0,-1,0)
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,//face 2
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,//face 1 upper
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,//face 3 closest
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,//face 4 (0,0,1)
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,//face 5 upper (1,0,0)
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,//face 5
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,//face 6 (0,1,0)
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,//face 6 closest
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,//face 4 upper
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

GLfloat vertex_data[] = {
	-1.0f,-1.0f,1.0f, //(0,-1,0)
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,1.0f,-1.0f, //(-1,0,0)
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	-1.0f,1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,1.0f,-1.0f, //(0,0,-1)
	-1.0f,1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,1.0f,1.0f, //(0,1,0)
	1.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f,
	-1.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f,
	-1.0f,1.0f,-1.0f,
	1.0f,1.0f,-1.0f, //(1,0,0)
	1.0f,1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,1.0f,-1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,1.0f,1.0f, //(0,0,1)
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
};

GLfloat instance_positions[] = {
	0,0,0,
	0,0,2,
	2,0,0,
};

GLfloat g_uv_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};

GLfloat vertices2[] = {
	-0.5f, -1.5f, -0.5f,
	0.5f, -1.5f, -0.5f,
	0.0f,  -0.5f, -0.5f
};

TGLBase gl_base;


std::vector <GLfloat> create_uv_map(std::vector <face_map_pair> pairs)
{
	std::vector <GLfloat> out_vector(72);
	int image_width = 256;
	int image_height = 256;
	int image_divisions_x = 16;
	int image_divisions_y = 16;
	for (auto it = pairs.begin(); it != pairs.end(); ++it)
	{
		int offset = (*it).normal * 12;
		
		out_vector[0 + offset] = (((*it).x*1.0)/image_divisions_x);
		out_vector[0 + offset + 1] = 1 - (((*it).y*1.0 + 1)/image_divisions_y);
		out_vector[2 + offset] = (((*it).x*1.0 + 1) / image_divisions_x);
		out_vector[2 + offset + 1] = 1 - (((*it).y*1.0 + 1) / image_divisions_y);
		out_vector[4 + offset] = (((*it).x*1.0 + 1) / image_divisions_x);
		out_vector[4 + offset + 1] = 1 - (((*it).y*1.0) / image_divisions_y);
		out_vector[6 + offset] = (((*it).x*1.0) / image_divisions_x);
		out_vector[6 + offset + 1] = 1 - (((*it).y*1.0 + 1) / image_divisions_y);
		out_vector[8 + offset] = (((*it).x*1.0 + 1) / image_divisions_x);
		out_vector[8 + offset + 1] = 1 - (((*it).y*1.0) / image_divisions_y);
		out_vector[10 + offset] = (((*it).x*1.0) / image_divisions_x);
		out_vector[10 + offset + 1] = 1 - (((*it).y*1.0) / image_divisions_y);
		/*
		out_vector[0 + offset] = 0.0f;
		out_vector[0 + offset + 1] = 1.0f;
		out_vector[2 + offset] = 1.0f / 2;
		out_vector[2 + offset + 1] = 1.0f;
		out_vector[4 + offset] = 1.0f / 2;
		out_vector[4 + offset + 1] = 1.0f - 1.0/2;
		out_vector[6 + offset] = 0.0f;
		out_vector[6 + offset + 1] = 1.0f;
		out_vector[8 + offset] = 1.0f / 2;
		out_vector[8 + offset + 1] = 1.0f - 1.0 / 2;
		out_vector[10 + offset] = 0.0f;
		out_vector[10 + offset + 1] = 1.0f - 1.0 / 2;
		*/
	}
	return out_vector;
}

int main()
{
	
	TGLActor test_actor;
	GLfloat * instances = new GLfloat[10*65536*3];
	std::vector <GLfloat> dirt_with_grass;
	std::vector <GLfloat> dirt;
	{	
		face_map_pair bottom, left_x, forward_y, backward_y, right_x, top;
		bottom.normal = 0; bottom.x = 2; bottom.y = 15;
		left_x.normal = 1; left_x.x = 3; left_x.y = 15;
		forward_y.normal = 5; forward_y.x = 3; forward_y.y = 15;
		backward_y.normal = 2; backward_y.x = 3; backward_y.y = 15;
		right_x.normal = 4; right_x.x = 3; right_x.y = 15;
		top.normal = 3; top.x = 0; top.y = 15;

		std::vector <face_map_pair> new_pairs = { bottom, left_x, forward_y, backward_y, right_x, top };

		dirt_with_grass = create_uv_map(new_pairs);
	}
	{
		face_map_pair bottom, left_x, forward_y, backward_y, right_x, top;
		bottom.normal = 0; bottom.x = 2; bottom.y = 15;
		left_x.normal = 1; left_x.x = 2; left_x.y = 15;
		forward_y.normal = 5; forward_y.x = 2; forward_y.y = 15;
		backward_y.normal = 2; backward_y.x = 2; backward_y.y = 15;
		right_x.normal = 4; right_x.x = 2; right_x.y = 15;
		top.normal = 3; top.x = 2; top.y = 15;

		std::vector <face_map_pair> new_pairs = { bottom, left_x, forward_y, backward_y, right_x, top };

		dirt = create_uv_map(new_pairs);
	}
	for (int n = 0; n < 1; n++)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				for (int k = 0; k < 16; k++)
				{
					instances[3 * 256 * i + 3 * 16 * j + 3 * k + 3*n * 65536] = 2 * k + n*32;
					instances[3 * 256 * i + 3 * 16 * j + 3 * k + 2 + 3 * n * 65536] = 2 * j;
					instances[3 * 256 * i + 3 * 16 * j + 3 * k + 1 + 3 * n * 65536] = 2 * i;
				}
			}
		}
	}

	gl_base.init();
	TGLTexture cube_tex("content/textures/mc.png");
	std::vector<GLfloat> v(vertex_data, vertex_data + sizeof vertex_data / sizeof vertex_data[0]);
	//TGLMeshVertices mesh_v(v);
	//TGLMesh tri_mesh(&mesh_v);
	//TGLMaterial tri_mat;
	//tri_mat.add_texture(&cube_tex, &dirt_with_grass[0], 72);
	//TGLMesh tri_mesh2(vertex_data, 108);
	
	//TGLShader v_shader("vertex_shader.glsl", GL_VERTEX_SHADER);
	//TGLShader f_shader("fragment_shader.glsl", GL_FRAGMENT_SHADER);
	//tri_mat.add_shader(&v_shader);
	//tri_mat.add_shader(&f_shader);
	//tri_mat.link_shader();
	//tri_mesh.set_material(&tri_mat);

	TGLChunkSpawn chunk_spawn;
	gl_base.set_world_actor((TGLActor*)&chunk_spawn);
	//tri_mesh2.add_shader(&v_shader);
	//tri_mesh2.add_shader(&f_shader);
	//tri_mesh2.link_shader();

	
	//tri_mesh2.add_texture(&cube_tex, &dirt[0], 72);

	//tri_mesh2.set_transform(glm::translate(tri_mesh2.get_transform(), glm::vec3(0.0f, 0.0f, 0.0f)));
	//tri_mesh2.set_transform(glm::rotate(tri_mesh2.get_transform(), 3.14159f/2, glm::vec3(0.0f, 1.0f, 0.0f)));
	TGLPlayer main_cam;

	//test_actor.add_component(&tri_mesh);
	//test_actor.add_component(&tri_mesh2);
	//tri_mesh2.enable_instancing(instances, 256);
	//tri_mesh.enable_instancing(&instances[256*3], 256);

	//gl_base.add_mesh(&tri_mesh);
	//gl_base.add_mesh(&tri_mesh2);
	gl_base.add_camera(&main_cam);
	gl_base.add_actor(&main_cam);
	gl_base.add_actor(&chunk_spawn);
	//gl_base.add_actor(&test_actor);
	//test_actor.set_transform(glm::scale(test_actor.get_transform(), glm::vec3(.3f)));
	//gl_base.load_model(vertices);
	while (1)
	{
		gl_base.update();
		//test_actor.translate(glm::vec3(0.0f, 0.0f, 0.01f));
		//test_actor.rotate(0.001f, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	return 0;
}