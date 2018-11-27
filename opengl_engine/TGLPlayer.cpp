#include "TGLPlayer.h"

#include "TGLBase.h"
#include <glm/gtx/matrix_decompose.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "useful_structures.h"

//extern std::vector <GLfloat> vertex_data_block_small;
extern TGLBase gl_base;

TGLPlayer::TGLPlayer():
	inventory(10, 10)
{
	glfwSetInputMode(gl_base.get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	x_angle = 0;
	y_angle = 0;

	set_view(glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 5.0f, -5.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)));

	TGLBounds * new_bounds = new TGLBlockBounds(0.9, 3.2, 0.9);
	set_bounds(new_bounds);
	mass = 68;
	hitting = glm::vec3(0,300,0);
	
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
		//add_component(temp_mesh);
		temp_mesh->translate(glm::vec3(2.0, 0, 0.0));
		temp_mesh->is_child = true;
		debug_block = temp_mesh;
	}
}


TGLPlayer::~TGLPlayer()
{
}


extern TGLActor debug_actor;

void TGLPlayer::tick(double time_delta)
{
	double xpos, ypos;
	static float debug_rot = 0.0;
	debug_rot +=  5;
	
	glm::vec3 up_vector(0.0, 1.0, 0.0);
	up_vector = glm::mat3(get_rot())*up_vector;
	glm::vec3 x_vector(1.0, 0.0, 0.0);
	glfwGetCursorPos(gl_base.get_window(), &xpos, &ypos);
	x_angle += ypos*3.14159 / 5000;
	while (x_angle > 3.14159)
	{
		x_angle -= 2 * 3.14159;
	}
	while (x_angle < -3.14159)
	{
		x_angle += 2 * 3.14159;
	}
	y_angle += xpos*3.14159 / 5000;
	while (y_angle > 3.14159)
	{
		y_angle -= 2 * 3.14159;
	}
	while (y_angle < -3.14159)
	{
		y_angle += 2 * 3.14159;
	}
	set_rot(glm::mat4(1.0));
	//set_rot(glm::quat());

	
	rotate(-y_angle, glm::vec3(0, 1.0, 0));
	rotate(-x_angle, glm::vec3(0.0, 0.0, 1.0));

	x_vector = glm::mat3(get_rot())*x_vector;
	
	if (int(debug_rot) % 1000 == 0)
	{
		debug_rot = 0;
		std::cout << "Y POS " << pos.y << ", " << "X POS" << pos.x << ", " << "Z POS" << pos.z << "\n";
	}
	
	//std::cout << "DEBUG Y POS " << debug_block->pos.y << ", " << "X POS" << debug_block->pos.x << ", " << "Z POS" << debug_block->pos.z << "\n";
	glfwSetCursorPos(gl_base.get_window(), 0, 0);

	glm::vec3 forward_vector_crosshair(1.0, 0.0, 0.0);

	forward_vector_crosshair = glm::mat3(get_rot())*forward_vector_crosshair;
	//forward_vector += pos;
	//forward_vector += glm::vec3(0.0, 0.5, 0);

	crosshair = forward_vector_crosshair;

	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_W) == GLFW_PRESS)
	{
		//glm::vec3 forward_vector(time_delta * 50 * sin(-y_angle), vel.y, time_delta*50*cos(-y_angle));
		
		//glm::quat move_rot = glm::quat(0, glm::vec3(0.0, 1.0, 0.0));
		//vel = forward_vector;
		//translate(forward_vector);
		glm::vec3 forward_vector(10.0, 0.0, 0.0);

		forward_vector = glm::mat3(get_rot())*forward_vector;
		forward_vector.y = 0;
		//translate(forward_vector);
		vel.x = forward_vector.x;
		vel.z = forward_vector.z;
		//debug_block->set_pos(glm::vec3(0, 0, 2.0));
	}
	else
	{
		vel.x = 0;
		vel.z = 0;
	}
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_S) == GLFW_PRESS)
	{
		glm::vec3 forward_vector(0.0, 0.0, time_delta*-30);

		forward_vector = forward_vector*glm::mat3(get_rot());
		
	}
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (get_on_ground())
		{
			vel.y += 5;
		}
	}
	if (glfwGetMouseButton(gl_base.get_window(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		glm::vec3 forward_vector(1.0, 0.0, 0.0);
		
		forward_vector = glm::mat3(get_rot())*forward_vector;
		//forward_vector += pos;
		//forward_vector += glm::vec3(0.0, 0.5, 0);
		
		set_hitting(forward_vector);
	}
	else
	{
		set_hitting(glm::vec3(0, 300, 0));
	}
	glm::vec3 light_grey = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 mid_grey = glm::vec3(0.35, 0.35, 0.35);
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_1) == GLFW_PRESS)
	{
		equipped_item = inventory.get_item(0, 0);
		hud[0]->sub_elements[0]->color = light_grey;
		hud[0]->sub_elements[2]->color = mid_grey;
		hud[0]->sub_elements[4]->color = mid_grey;
		hud[0]->sub_elements[6]->color = mid_grey;
		hud[0]->sub_elements[8]->color = mid_grey;
	}
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_2) == GLFW_PRESS)
	{
		equipped_item = inventory.get_item(1, 0);
		hud[0]->sub_elements[0]->color = mid_grey;
		hud[0]->sub_elements[2]->color = light_grey;
		hud[0]->sub_elements[4]->color = mid_grey;
		hud[0]->sub_elements[6]->color = mid_grey;
		hud[0]->sub_elements[8]->color = mid_grey;
	}
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_3) == GLFW_PRESS)
	{
		equipped_item = inventory.get_item(2, 0);
		hud[0]->sub_elements[0]->color = mid_grey;
		hud[0]->sub_elements[2]->color = mid_grey;
		hud[0]->sub_elements[4]->color = light_grey;
		hud[0]->sub_elements[6]->color = mid_grey;
		hud[0]->sub_elements[8]->color = mid_grey;
	}
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_4) == GLFW_PRESS)
	{
		equipped_item = inventory.get_item(3, 0);
		hud[0]->sub_elements[0]->color = mid_grey;
		hud[0]->sub_elements[2]->color = mid_grey;
		hud[0]->sub_elements[4]->color = mid_grey;
		hud[0]->sub_elements[6]->color = light_grey;
		hud[0]->sub_elements[8]->color = mid_grey;
	}
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_5) == GLFW_PRESS)
	{
		equipped_item = inventory.get_item(4, 0);
		hud[0]->sub_elements[0]->color = mid_grey;
		hud[0]->sub_elements[2]->color = mid_grey;
		hud[0]->sub_elements[4]->color = mid_grey;
		hud[0]->sub_elements[6]->color = mid_grey;
		hud[0]->sub_elements[8]->color = light_grey;
	}
	
	TGLInventoryItem * next_item = inventory.get_item(0, 0);
	if (next_item != nullptr)
	{
		hud[0]->sub_elements[1]->set_offsets(useful_structures::item_id_to_texture_coords[next_item->type], useful_structures::item_id_to_texture_coords[next_item->type] + glm::vec2(16, 16));
	}
	else
	{
		hud[0]->sub_elements[1]->set_offsets(glm::vec2(16, 8 * 16), glm::vec2(16, 8 * 16) + glm::vec2(16, 16));
	}
	next_item = inventory.get_item(1, 0);
	if (next_item != nullptr)
	{
		hud[0]->sub_elements[3]->set_offsets(useful_structures::item_id_to_texture_coords[next_item->type], useful_structures::item_id_to_texture_coords[next_item->type] + glm::vec2(16, 16));
	}
	else
	{
		hud[0]->sub_elements[3]->set_offsets(glm::vec2(16, 8 * 16), glm::vec2(16, 8 * 16) + glm::vec2(16, 16));
	}
	next_item = inventory.get_item(2, 0);
	if (next_item != nullptr)
	{
		hud[0]->sub_elements[5]->set_offsets(useful_structures::item_id_to_texture_coords[next_item->type], useful_structures::item_id_to_texture_coords[next_item->type] + glm::vec2(16, 16));
	}
	else
	{
		hud[0]->sub_elements[5]->set_offsets(glm::vec2(16, 8 * 16), glm::vec2(16, 8 * 16) + glm::vec2(16, 16));
	}
	next_item = inventory.get_item(3, 0);
	if (next_item != nullptr)
	{
		hud[0]->sub_elements[7]->set_offsets(useful_structures::item_id_to_texture_coords[next_item->type], useful_structures::item_id_to_texture_coords[next_item->type] + glm::vec2(16, 16));
	}
	else
	{
		hud[0]->sub_elements[7]->set_offsets(glm::vec2(16, 8 * 16), glm::vec2(16, 8 * 16) + glm::vec2(16, 16));
	}
	next_item = inventory.get_item(4, 0);
	if (next_item != nullptr)
	{
		hud[0]->sub_elements[9]->set_offsets(useful_structures::item_id_to_texture_coords[next_item->type], useful_structures::item_id_to_texture_coords[next_item->type] + glm::vec2(16, 16));
	}
	else
	{
		hud[0]->sub_elements[9]->set_offsets(glm::vec2(16, 8 * 16), glm::vec2(16, 8 * 16) + glm::vec2(16, 16));
	}


	glm::vec3 forward_vector2(0.0, 0.0, 2);

	//forward_vector2 = forward_vector2*get_rot();
	//forward_vector2 = forward_vector2 + get_pos();
	//debug_block->set_pos(glm::vec3(0,0,0));
	
	//debug_block->set_pos(forward_vector2);
	//debug_block->set_rot(get_rot());
	//debug_block->rotate(-x_angle, glm::vec3(-1.0, 0.0, 0.0));
	//debug_block->rotate(y_angle, glm::vec3(0, 1.0, 0));
	
	
}

void TGLPlayer::set_hitting(glm::vec3 in_hitting)
{
	hitting = in_hitting;
}

glm::vec3 TGLPlayer::get_hitting()
{
	return hitting;
}

void TGLPlayer::add_hud(TGLHudElement * in_hud)
{
	hud.push_back(in_hud);
}

TGLInventoryItem& TGLPlayer::get_equipped()
{
	return *equipped_item;
}

bool TGLPlayer::change_inventory_amount(TGLItemId item_type, int in_amount)
{
	return inventory.change_quantity(item_type, in_amount);
}