#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "TGLBase.h"
#include "TGLCamera.h"
#include "TGLPlayer.h"
#include "TGLChunkSpawn.h"
#include "useful_structures.h"


//extern std::vector <GLfloat> useful_structures::vertex_data_block_small;

TGLBase gl_base;
TGLActor debug_actor;

TGLMesh * create_cube_mesh()
{
	TGLMeshVertices * block_mesh_vertices = new TGLMeshVertices(useful_structures::vertex_data_block_small);
	TGLMesh * temp_mesh = new TGLMesh(block_mesh_vertices);
	TGLMaterial * temp_mat = new TGLMaterial();

	TGLShader v_shader("vertex_shader.glsl", GL_VERTEX_SHADER);
	TGLShader f_shader("fragment_shader.glsl", GL_FRAGMENT_SHADER);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}

	temp_mat->add_shader(&v_shader);
	temp_mat->add_shader(&f_shader);
	temp_mat->link_shader();

	//temp_mesh->set_material(block_material, 0);
	temp_mesh->set_material(temp_mat);
	return temp_mesh;
}

class rot_actor : public TGLActor
{
	void tick(double time_delta)
	{
		static_physics = true;
		static float d_rot = 0;
		d_rot += 0.01;
		glm::mat4 out_transform(1.0);
		out_transform = glm::translate(out_transform, glm::vec3(0, 195, 0));
		out_transform = glm::rotate(out_transform, d_rot, glm::vec3(0, 0, 1));
		out_transform = glm::rotate(out_transform, d_rot, glm::vec3(0, 1, 0));
		
		
		set_transform(out_transform);
	}
};

int main()
{
	gl_base.init();
	
	TGLHudElement inventory(600, 120, glm::vec2(100,100), glm::vec3(0.2, 0.2, 0.2));
	int offset = 10;
	int shift = 120;
	TGLHudElement inventory_item(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/pickaxe.png");
	TGLHudElement inventory_itemb(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	TGLHudElement inventory_item2(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png", 0, 0, 16, 16);
	TGLHudElement inventory_item2b(120, 120, glm::vec2(offset-10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	TGLHudElement inventory_item3(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png");
	TGLHudElement inventory_item3b(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	TGLHudElement inventory_item4(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png");
	TGLHudElement inventory_item4b(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	TGLHudElement inventory_item5(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png");
	TGLHudElement inventory_item5b(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	inventory.sub_elements.push_back(&inventory_itemb);
	inventory.sub_elements.push_back(&inventory_item);
	inventory.sub_elements.push_back(&inventory_item2b);
	inventory.sub_elements.push_back(&inventory_item2);
	inventory.sub_elements.push_back(&inventory_item3b);
	inventory.sub_elements.push_back(&inventory_item3);
	inventory.sub_elements.push_back(&inventory_item4b);
	inventory.sub_elements.push_back(&inventory_item4);
	inventory.sub_elements.push_back(&inventory_item5b);
	inventory.sub_elements.push_back(&inventory_item5);

	debug_actor.add_component(create_cube_mesh());
	debug_actor.set_scale(glm::vec3(0.1,0.1,0.1));

	TGLChunkSpawn chunk_spawn;
	gl_base.set_world_actor((TGLActor*)&chunk_spawn);

	TGLPlayer main_cam;
	main_cam.add_hud(&inventory);
	gl_base.add_camera(&main_cam);
	gl_base.add_actor(&main_cam);
	gl_base.add_actor(&chunk_spawn);
	gl_base.add_actor(&debug_actor);
	gl_base.add_hud_element(&inventory);
	//debug_actor.set_pos(glm::vec3(0, 185, 0));
	while (1)
	{
		gl_base.update();
	}

	return 0;
}