#include "TGLChunkSpawn.h"
#include "TGLBase.h"
#include "block_vertices.h"

#define PI 3.1415926

extern TGLBase gl_base;
/*
std::vector <GLfloat> vertex_data_block_small = {
-0.5f, -0.5f, 0.5f, //(0,-1,0)
0.5f, -0.5f, 0.5f,
0.5f, -0.5f, -0.5f,
-0.5f, -0.5f, 0.5f,
0.5f, -0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
-0.5f, 0.5f, -0.5f, //(-1,0,0)
-0.5f, 0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,
-0.5f, 0.5f, -0.5f,
-0.5f, -0.5f, 0.5f,
-0.5f, -0.5f, -0.5f,
0.5f, 0.5f, -0.5f, //(0,0,-1)
-0.5f, 0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
0.5f, 0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
-0.5f, 0.5f, 0.5f, //(0,1,0)
0.5f, 0.5f, 0.5f,
0.5f, 0.5f, -0.5f,
-0.5f, 0.5f, 0.5f,
0.5f, 0.5f, -0.5f,
-0.5f, 0.5f, -0.5f,
0.5f, 0.5f, -0.5f, //(1,0,0)
0.5f, 0.5f, 0.5f,
0.5f, -0.5f, 0.5f,
0.5f, 0.5f, -0.5f,
0.5f, -0.5f, 0.5f,
0.5f, -0.5f, -0.5f,
0.5f, 0.5f, 0.5f, //(0,0,1)
-0.5f, 0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,
0.5f, 0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,
0.5f, -0.5f, 0.5f,
};
*/


TGLChunkSpawn::TGLChunkSpawn():block_type_count(7),test_chunk(false)
{
	block_generator = new BlockGenerator(test_chunk);

	std::vector <GLfloat> dirt_with_grass;
	std::vector <GLfloat> dirt;
	std::vector <GLfloat> stone;
	std::vector <GLfloat> tree;
	std::vector <GLfloat> leaves;
	std::vector <GLfloat> water;
	std::vector <GLfloat> sand;
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
	{
		face_map_pair bottom, left_x, forward_y, backward_y, right_x, top;
		bottom.normal = 0; bottom.x = 1; bottom.y = 15;
		left_x.normal = 1; left_x.x = 1; left_x.y = 15;
		forward_y.normal = 5; forward_y.x = 1; forward_y.y = 15;
		backward_y.normal = 2; backward_y.x = 1; backward_y.y = 15;
		right_x.normal = 4; right_x.x = 1; right_x.y = 15;
		top.normal = 3; top.x = 1; top.y = 15;

		std::vector <face_map_pair> new_pairs = { bottom, left_x, forward_y, backward_y, right_x, top };

		stone = create_uv_map(new_pairs);
	}
	{
		face_map_pair bottom, left_x, forward_y, backward_y, right_x, top;
		bottom.normal = 0; bottom.x = 5; bottom.y = 14;
		left_x.normal = 1; left_x.x = 4; left_x.y = 14;
		forward_y.normal = 5; forward_y.x = 4; forward_y.y = 14;
		backward_y.normal = 2; backward_y.x = 4; backward_y.y = 14;
		right_x.normal = 4; right_x.x = 4; right_x.y = 14;
		top.normal = 3; top.x = 5; top.y = 14;

		std::vector <face_map_pair> new_pairs = { bottom, left_x, forward_y, backward_y, right_x, top };

		tree = create_uv_map(new_pairs);
	}
	{
		face_map_pair bottom, left_x, forward_y, backward_y, right_x, top;
		bottom.normal = 0; bottom.x = 4; bottom.y = 12;
		left_x.normal = 1; left_x.x = 4; left_x.y = 12;
		forward_y.normal = 5; forward_y.x = 4; forward_y.y = 12;
		backward_y.normal = 2; backward_y.x = 4; backward_y.y = 12;
		right_x.normal = 4; right_x.x = 4; right_x.y = 12;
		top.normal = 3; top.x = 4; top.y = 12;

		std::vector <face_map_pair> new_pairs = { bottom, left_x, forward_y, backward_y, right_x, top };

		leaves = create_uv_map(new_pairs);
	}
	{
		face_map_pair bottom, left_x, forward_y, backward_y, right_x, top;
		bottom.normal = 0; bottom.x = 13; bottom.y = 3;
		left_x.normal = 1; left_x.x = 13; left_x.y = 3;
		forward_y.normal = 5; forward_y.x = 13; forward_y.y = 3;
		backward_y.normal = 2; backward_y.x = 13; backward_y.y = 3;
		right_x.normal = 4; right_x.x = 13; right_x.y = 3;
		top.normal = 3; top.x = 13; top.y = 3;

		std::vector <face_map_pair> new_pairs = { bottom, left_x, forward_y, backward_y, right_x, top };

		water = create_uv_map(new_pairs);
	}
	{
		face_map_pair bottom, left_x, forward_y, backward_y, right_x, top;
		bottom.normal = 0; bottom.x = 2; bottom.y = 14;
		left_x.normal = 1; left_x.x = 2; left_x.y = 14;
		forward_y.normal = 5; forward_y.x = 2; forward_y.y = 14;
		backward_y.normal = 2; backward_y.x = 2; backward_y.y = 14;
		right_x.normal = 4; right_x.x = 2; right_x.y = 14;
		top.normal = 3; top.x = 2; top.y = 14;

		std::vector <face_map_pair> new_pairs = { bottom, left_x, forward_y, backward_y, right_x, top };

		sand = create_uv_map(new_pairs);
	}
	
	block_texture = new TGLTexture("content/textures/mc.png");
	block_material = new TGLMaterial;

	block_mesh_vertices = new TGLMeshVertices(vertex_data_block_small);
	
	TGLShader v_shader("vertex_shader.glsl", GL_VERTEX_SHADER);
	TGLShader f_shader("fragment_shader.glsl", GL_FRAGMENT_SHADER);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}

	block_material->add_shader(&v_shader);
	block_material->add_shader(&f_shader);
	block_material->link_shader();

	block_material->add_texture(block_texture, &dirt_with_grass[0], 72);
	block_material->add_texture(block_texture, &dirt[0], 72);
	block_material->add_texture(block_texture, &stone[0], 72);
	block_material->add_texture(block_texture, &tree[0], 72);
	block_material->add_texture(block_texture, &leaves[0], 72);
	block_material->add_texture(block_texture, &water[0], 72);
	block_material->add_texture(block_texture, &sand[0], 72);
	//TGLMesh tri_mesh2(vertex_data, 108);
	
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}
	return;
	for (int i = -5; i < 5; ++i)
	{
		for (int j = -5; j < 5; ++j)
		{
			spawn_chunk(i, j);
		}
	}
	
}

enum dir
{
	dir_x,
	dir_y,
	dir_z,
	dir_neg_x,
	dir_neg_y,
	dir_neg_z
};

glm::vec3 get_closest_boundary(glm::vec3 in_vec, glm::vec3 origin, dir& out_dir)
{
	glm::vec3 x_next, y_next, z_next;
	if (in_vec.x == 0)
	{
		x_next = glm::vec3(300, 300, 300);
	}
	else if (in_vec.x > 0)
	{
		x_next = in_vec*float((ceil(in_vec.x + origin.x)-origin.x) / in_vec.x)*1.01f;
	}
	else
	{
		x_next = in_vec*float((floor(in_vec.x + origin.x) - origin.x) / in_vec.x)*0.99f;
	}
	if (in_vec.y == 0)
	{
		y_next = glm::vec3(300, 300, 300);
	}
	else if (in_vec.y > 0)
	{
		y_next = in_vec*float((ceil(in_vec.y + origin.y) - origin.y) / in_vec.y)*1.01f;
	}
	else
	{
		y_next = in_vec*float((floor(in_vec.y + origin.y) - origin.y) / in_vec.y)*0.99f;
	}
	if (in_vec.z == 0)
	{
		z_next = glm::vec3(300, 300, 300);
	}
	else if (in_vec.z > 0)
	{
		z_next = in_vec*float((ceil(in_vec.z + origin.z) - origin.z) / in_vec.z)*1.01f;
	}
	else
	{
		z_next = in_vec*float((floor(in_vec.z + origin.z) - origin.z) / in_vec.z)*0.99f;
	}
	if (glm::length(y_next) < glm::length(x_next))
	{
		if (glm::length(z_next) < glm::length(y_next))
		{
			if (z_next.z < 0)
			{
				out_dir = dir_neg_z;
			}
			else
			{
				out_dir = dir_z;
			}
			return origin + z_next;
		}

		if (y_next.y < 0)
		{
			out_dir = dir_neg_y;
		}
		else
		{
			out_dir = dir_y;
		}
		return origin + y_next;
	}
	if (x_next.x < 0)
	{
		out_dir = dir_neg_x;
	}
	else
	{
		out_dir = dir_x;
	}
	return origin + x_next;
}


extern TGLActor debug_actor;
glm::vec3 get_forward_blocks(glm::vec3 origin, glm::vec3 forward, BlockGenerator * generator, dir& out_dir)
{
	float max_distance = 5.0;
	float distance = 0.5;
	glm::vec3 point = get_closest_boundary(distance*forward, origin, out_dir);
	if (abs(round(point.x) - point.x) < abs(round(point.y) - point.y))
	{
		if (abs(round(point.x) - point.x) < abs(round(point.z) - point.z))
		{
			if (forward.x < 0)
			{
				out_dir = dir_neg_x;
			}
			else
			{
				out_dir = dir_x;
			}
		}
		else
		{
			if (forward.z < 0)
			{
				out_dir = dir_neg_z;
			}
			else
			{
				out_dir = dir_z;
			}
		}
	}
	else
	{
		if (abs(round(point.y) - point.y) < abs(round(point.z) - point.z))
		{
			if (forward.y < 0)
			{
				out_dir = dir_neg_y;
			}
			else
			{
				out_dir = dir_y;
			}
		}
		else
		{
			if (forward.z < 0)
			{
				out_dir = dir_neg_z;
			}
			else
			{
				out_dir = dir_z;
			}
		}
	}
	while (1)
	{

		if (generator->get_point(round(point.x), round(point.z), round(point.y)) != 0 && glm::length(forward) < max_distance)
		{
			debug_actor.set_pos(point);
			return glm::vec3(round(point.x), round(point.y), round(point.z));
		}
		distance = glm::length(point - origin);
		distance += 0.1;
		point = get_closest_boundary(distance*forward, origin, out_dir);
		
		if (abs(round(point.x) - point.x) < abs(round(point.y) - point.y))
		{
			if (abs(round(point.x) - point.x) < abs(round(point.z) - point.z))
			{
				if (forward.x < 0)
				{
					out_dir = dir_neg_x;
				}
				else
				{
					out_dir = dir_x;
				}
			}
			else
			{
				if (forward.z < 0)
				{
					out_dir = dir_neg_z;
				}
				else
				{
					out_dir = dir_z;
				}
			}
		}
		else
		{
			if (abs(round(point.y) - point.y) < abs(round(point.z) - point.z))
			{
				if (forward.y < 0)
				{
					out_dir = dir_neg_y;
				}
				else
				{
					out_dir = dir_y;
				}
			}
			else
			{
				if (forward.z < 0)
				{
					out_dir = dir_neg_z;
				}
				else
				{
					out_dir = dir_z;
				}
			}
		}

		if (glm::length(point - origin) > max_distance)
		{
			return glm::vec3(100, 300, 0);
		}
	}
}



template <typename T> int sign(T val) {
	return (T(0) < val) - (val < T(0));
}

glm::vec3 ray_cast_block_finder(glm::vec3 in_position, glm::vec3 in_ray, glm::vec3 ray_start, glm::vec3& next_ray)
{
	double next_x_intersect_x,
		next_x_intersect_y,
		next_x_intersect_z,
		next_y_intersect_x,
		next_y_intersect_y,
		next_y_intersect_z,
		next_z_intersect_x,
		next_z_intersect_y,
		next_z_intersect_z;

	double x_length,
		y_length,
		z_length;


	glm::vec3 next_x_ray,
		next_y_ray,
		next_z_ray;

	glm::vec3 x_intersected_block,
		y_intersected_block,
		z_intersected_block,
		intersected_block;


	if (in_ray.x != 0)
	{
		next_x_intersect_x = round(ray_start.x) + 0.5*sign(in_ray.x);
		next_x_intersect_y = in_position.y + (ray_start.y - in_position.y)*(next_x_intersect_x - in_position.x) / (ray_start.x - in_position.x);
		next_x_intersect_z = in_position.z + (ray_start.z - in_position.z)*(next_x_intersect_x - in_position.x) / (ray_start.x - in_position.x);
		next_x_ray = glm::vec3(next_x_intersect_x - in_position.x, next_x_intersect_y - in_position.y, next_x_intersect_z - in_position.z);
		x_length = glm::length(next_x_ray);
		x_intersected_block = glm::vec3(round(next_x_intersect_x + 0.1*sign(in_ray.x)), round(next_x_intersect_y), round(next_x_intersect_z));
	}
	else
	{
		x_length = 1000;
	}

	if (in_ray.y != 0)
	{
		next_y_intersect_y = round(ray_start.y) + 0.5*sign(in_ray.y);
		next_y_intersect_z = in_position.z + (ray_start.z - in_position.z)*(next_y_intersect_y - in_position.y) / (ray_start.y - in_position.y);
		next_y_intersect_x = in_position.x + (ray_start.x - in_position.x)*(next_y_intersect_y - in_position.y) / (ray_start.y - in_position.y);
		next_y_ray = glm::vec3(next_y_intersect_x - in_position.x, next_y_intersect_y - in_position.y, next_y_intersect_z - in_position.z);
		y_length = glm::length(next_y_ray);
		y_intersected_block = glm::vec3(round(next_y_intersect_x), round(next_y_intersect_y + 0.1*sign(in_ray.y)), round(next_y_intersect_z));
	}
	else
	{
		y_length = 1000;
	}

	if (in_ray.z != 0)
	{
		next_z_intersect_z = round(ray_start.z) + 0.5*sign(in_ray.z);
		next_z_intersect_y = in_position.y + (ray_start.y - in_position.y)*(next_z_intersect_z - in_position.z) / (ray_start.z - in_position.z);
		next_z_intersect_x = in_position.x + (ray_start.x - in_position.x)*(next_z_intersect_z - in_position.z) / (ray_start.z - in_position.z);
		next_z_ray = glm::vec3(next_z_intersect_x - in_position.x, next_z_intersect_y - in_position.y, next_z_intersect_z - in_position.z);
		z_length = glm::length(next_z_ray);
		z_intersected_block = glm::vec3(round(next_z_intersect_x), round(next_z_intersect_y), round(next_z_intersect_z + 0.1*sign(in_ray.z)));
	}
	else
	{
		z_length = 1000;
	}

	if (x_length < z_length && x_length < y_length)
	{
		intersected_block = x_intersected_block;
		next_ray = next_x_ray;
	}
	else if (y_length < z_length && y_length < x_length)
	{
		intersected_block = y_intersected_block;
		next_ray = next_y_ray;
	}
	else if (z_length < x_length && z_length < y_length)
	{
		intersected_block = z_intersected_block;
		next_ray = next_z_ray;
	}
	return intersected_block;
}

void TGLChunkSpawn::tick(double time_delta)
{
	static double time_sum = 0;
	time_sum += time_delta;
	if (time_sum > 0.1)
	{
		TGLPlayer * player = gl_base.get_player();
		glm::vec3 hitting = player->get_hitting();
		TGLInventoryItem& equipped = player->get_equipped();
		
		
		//hitting = glm::vec3(floor(hitting.x), floor(hitting.y), floor(hitting.z)+1);
		if (hitting.y < 256)// && glm::length(hitting - player->get_pos()) < 5)
		{
			dir out_dir;
			int block_type = 0;
			//hitting = get_forward_blocks(player->get_pos(), hitting, block_generator, out_dir);
			
			glm::vec3 next_ray = hitting*0.01f;
			glm::vec3 next_block = player->get_pos();
			glm::vec3 prev_block = next_block;
			while (block_type == 0 && glm::length(player->get_pos() - next_block) < 5)
			{
				prev_block = next_block;
				next_block = ray_cast_block_finder(player->get_pos(), hitting, player->get_pos() + next_ray*1.01f, next_ray);
				block_type = block_generator->get_point(next_block.x, next_block.z, next_block.y);
			}
			hitting = next_block;
			int chunk_x = floor(hitting.x / 16.0);
			int chunk_y = floor(hitting.z / 16.0);
			if (block_type)
			{
				
				if (test_chunk)
				{
					block_type = (abs(chunk_x + chunk_y) % 6) + 1;
				}
				std::cout << "REMOVING " << block_type << " FROM " << hitting.x - chunk_x * 16 << ", " << hitting.y << ", " << hitting.z - chunk_y * 16 << "\n";
				std::cout << "from chunk " << chunk_x << ", " << chunk_y << "\n";
				glm::vec3 to_remove((unsigned int)(hitting.x - chunk_x * 16), (unsigned int)(hitting.y), (unsigned int)(hitting.z - chunk_y * 16));

				if (equipped.type == pickaxe)
				{
					bool was_deleted = chunks[chunk_coord(chunk_x, chunk_y)]->remove_instance(block_type, to_remove);
					if (was_deleted)
					{
						block_generator->set_point(0, hitting.x, hitting.z, hitting.y);
					}

					glm::vec3 to_add(to_remove.x + 1, to_remove.y, to_remove.z);
					int new_block_type = block_generator->get_point(hitting.x + 1, hitting.z, hitting.y);
					if (new_block_type != 0)
					{
						chunks[chunk_coord(chunk_x, chunk_y)]->add_instance(new_block_type, to_add);
					}
					to_add = glm::vec3(to_remove.x - 1, to_remove.y, to_remove.z);
					new_block_type = block_generator->get_point(hitting.x - 1, hitting.z, hitting.y);
					if (new_block_type != 0)
					{
						chunks[chunk_coord(chunk_x, chunk_y)]->add_instance(new_block_type, to_add);
					}
					to_add = glm::vec3(to_remove.x, to_remove.y + 1, to_remove.z);
					new_block_type = block_generator->get_point(hitting.x, hitting.z, hitting.y + 1);
					if (new_block_type != 0)
					{
						chunks[chunk_coord(chunk_x, chunk_y)]->add_instance(new_block_type, to_add);
					}
					to_add = glm::vec3(to_remove.x, to_remove.y - 1, to_remove.z);
					new_block_type = block_generator->get_point(hitting.x, hitting.z, hitting.y - 1);
					if (new_block_type != 0)
					{
						chunks[chunk_coord(chunk_x, chunk_y)]->add_instance(new_block_type, to_add);
					}
					to_add = glm::vec3(to_remove.x, to_remove.y, to_remove.z + 1);
					new_block_type = block_generator->get_point(hitting.x, hitting.z + 1, hitting.y);
					if (new_block_type != 0)
					{
						chunks[chunk_coord(chunk_x, chunk_y)]->add_instance(new_block_type, to_add);
					}
					to_add = glm::vec3(to_remove.x, to_remove.y, to_remove.z - 1);
					new_block_type = block_generator->get_point(hitting.x, hitting.z - 1, hitting.y);
					if (new_block_type != 0)
					{
						chunks[chunk_coord(chunk_x, chunk_y)]->add_instance(new_block_type, to_add);
					}
				}
				else if (equipped.type == soil_block)
				{
					

					chunk_x = floor(hitting.x / 16.0);
					chunk_y = floor(hitting.z / 16.0);

					glm::vec3 to_create((unsigned int)(prev_block.x - chunk_x * 16), (unsigned int)(prev_block.y), (unsigned int)(prev_block.z - chunk_y * 16));

					chunks[chunk_coord(chunk_x, chunk_y)]->add_instance(7, to_create);
					block_generator->set_point(7, prev_block.x, prev_block.z, prev_block.y);
				}
			}
		}

		//printf("Player pos %f, %f\n", player->get_pos().x, player->get_pos().z);
		float first_angle = player->x_angle - PI / 12 - PI;
		while (first_angle > PI) { first_angle -= 2 * PI; }
		while (first_angle < PI) { first_angle += 2 * PI; }

		float second_angle = player->x_angle + PI / 12 - PI;
		while (second_angle > PI) { second_angle -= 2 * PI; }
		while (second_angle < PI) { second_angle += 2 * PI; }

		if (second_angle < first_angle)
		{
			float temp = first_angle;
			first_angle = second_angle;
			second_angle = temp;
		}

		chunks_to_load = get_chunks(-int(player->get_pos().x/16), -int(player->get_pos().z/16), 10, first_angle, second_angle);

		for (auto it = chunks_to_load.begin(); it != chunks_to_load.end(); ++it)
		{
			if (chunks.find((*it)) == chunks.end())
			{
				//printf("Spawning %d, %d\n", (*it).x, (*it).y);
				spawn_chunk((*it).x, (*it).y);
				break;
			}
		}
		time_sum = 0;
	}
	
}

void TGLChunkSpawn::spawn_chunk(int chunk_x, int chunk_y)
{
	std::vector <std::vector<GLfloat>> instances;
	for (int i = 0; i < block_type_count; ++i)
	{
		instances.push_back(std::vector<GLfloat>(99));
	}
	int count = 0;

	block_generator->get_points((chunk_x * 16 - 1), (chunk_y * 16 - 1), 0, 18);
	
	for (int i = 1; i < 17; ++i)
	{
		for (int j = 1; j < 17; ++j)
		{
			if (test_chunk)
			{
				int tp = abs(chunk_x + chunk_y) % 6;
				instances[tp].push_back(i-1);
				instances[tp].push_back(180);
				instances[tp].push_back(j-1);
			}
			else if (chunk_x == 0 && chunk_y == 0)
			{
				for (int k = 150; k < 256; k++)
				{
					instances[0].push_back(i-1);
					instances[0].push_back(k);
					instances[0].push_back(j - 1);
				}
			}
			else if (chunk_x == 5 && chunk_y == 0)
			{
				for (int k = 150; k < 256; k++)
				{
					instances[1].push_back(i - 1);
					instances[1].push_back(k);
					instances[1].push_back(j - 1);
				}
			}
			else if (chunk_x == 0 && chunk_y == 5)
			{
				for (int k = 150; k < 256; k++)
				{
					instances[2].push_back(i - 1);
					instances[2].push_back(k);
					instances[2].push_back(j - 1);
				}
			}
			else
			{
				//unsigned char block_type = block_generator->get_point(chunk_x * 16 - 1 + i, chunk_y * 16 - 1 + j, 0);
				//instances[0].push_back(i);
				//instances[0].push_back(int(block_type));
				//instances[0].push_back(j);
				for (int k = 1; k < 256; ++k)
				{
					unsigned char block_type = block_generator->index(i, j, k);

					//int block_type_test = block_generator->get_point((chunk_x * 16 - 1)+i, (chunk_y * 16 - 1)+j, k);
					//if (block_type != block_type_test && block_type != 5 && block_type != 4)
					//{
					//	printf("FART\n");
					//}
					if (block_type > 0 && block_generator->is_visible(i, j, k) && k > 150)
					{
						instances[block_type - 1].push_back(i-1);
						instances[block_type - 1].push_back(k);
						instances[block_type - 1].push_back(j-1);
					}
				}
			}
		}
	}


	//retval = test_chunk->Instance(block_generator, FVector(chunk_x * 16, chunk_y * 1600, -500), 0);

	chunks[chunk_coord(chunk_x, chunk_y)] = new TGLChunk(block_mesh_vertices, block_material, block_type_count, instances);
	//chunks[chunk_coord(chunk_x, chunk_y)]->translate(glm::vec3(16*chunk_x, -200, 16 * chunk_y));
	chunks[chunk_coord(chunk_x, chunk_y)]->translate(glm::vec3(16 * chunk_x, 0, 16 * chunk_y));
	gl_base.add_actor(chunks[chunk_coord(chunk_x, chunk_y)]);
}

std::vector <GLfloat> TGLChunkSpawn::create_uv_map(std::vector <face_map_pair> pairs)
{
	std::vector <GLfloat> out_vector(72);
	int image_width = 256;
	int image_height = 256;
	int image_divisions_x = 16;
	int image_divisions_y = 16;
	for (auto it = pairs.begin(); it != pairs.end(); ++it)
	{
		int offset = (*it).normal * 12;

		if ((*it).normal > 2)
		{
			out_vector[0 + offset] = (((*it).x*1.0) / image_divisions_x);
			out_vector[0 + offset + 1] = 1 - (((*it).y*1.0 + 1) / image_divisions_y);
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
		}
		else
		{
			out_vector[0 + offset] = (((*it).x*1.0) / image_divisions_x);
			out_vector[0 + offset + 1] = 1 - (((*it).y*1.0 + 1) / image_divisions_y);
			out_vector[4 + offset] = (((*it).x*1.0 + 1) / image_divisions_x);
			out_vector[4 + offset + 1] = 1 - (((*it).y*1.0 + 1) / image_divisions_y);
			out_vector[2 + offset] = (((*it).x*1.0 + 1) / image_divisions_x);
			out_vector[2 + offset + 1] = 1 - (((*it).y*1.0) / image_divisions_y);
			out_vector[6 + offset] = (((*it).x*1.0) / image_divisions_x);
			out_vector[6 + offset + 1] = 1 - (((*it).y*1.0 + 1) / image_divisions_y);
			out_vector[10 + offset] = (((*it).x*1.0 + 1) / image_divisions_x);
			out_vector[10 + offset + 1] = 1 - (((*it).y*1.0) / image_divisions_y);
			out_vector[8 + offset] = (((*it).x*1.0) / image_divisions_x);
			out_vector[8 + offset + 1] = 1 - (((*it).y*1.0) / image_divisions_y);
		}
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

bool TGLChunkSpawn::between_angles(float x, float y, float in_angle_1, float in_angle_2)
{
	float angle = atan2(y, x);
	return (angle > in_angle_1 && angle < in_angle_2 || angle + 2 * PI > in_angle_1 && angle + 2 * PI < in_angle_2 || angle - 2 * PI > in_angle_1 && angle - 2 * PI < in_angle_2);
}

std::vector <chunk_coord> TGLChunkSpawn::get_chunks(int x0, int y0, int radius, float view_angle_1, float view_angle_2)
{
	std::vector <chunk_coord> out_vecs;
	int first_radius = 5;
	for (int x = 0; x < radius; ++x)
	{
		for (int y = 0; y < radius; ++y)
		{
			if (x*x + y*y <= radius*radius)
			{
				if (between_angles(x, y, view_angle_1, view_angle_2) || x*x + y*y < first_radius*first_radius)
				{
					out_vecs.push_back(chunk_coord(x0 + x, y0 + y));
				}
				if (between_angles(-x, y, view_angle_1, view_angle_2) || x*x + y*y < first_radius*first_radius)
				{
					out_vecs.push_back(chunk_coord(x0 - x, y0 + y));
				}
				if (between_angles(x, -y, view_angle_1, view_angle_2) || x*x + y*y < first_radius*first_radius)
				{
					out_vecs.push_back(chunk_coord(x0 + x, y0 - y));
				}
				if (between_angles(-x, -y, view_angle_1, view_angle_2) || x*x + y*y < first_radius*first_radius)
				{
					out_vecs.push_back(chunk_coord(x0 - x, y0 - y));
				}
			}
		}
	}
	return out_vecs;
	for (int i = 0; i < radius; i++)
	{
		int x = i;
		int y = 0;
		int err = 0;
		while (x >= y)
		{
			if (between_angles(x, y, view_angle_1, view_angle_2) && std::find(out_vecs.begin(), out_vecs.end(), chunk_coord(x0 + x, y0 + y)) == out_vecs.end())
			{
				out_vecs.push_back(chunk_coord(x0 + x, y0 + y));
			}
			if (between_angles(y, x, view_angle_1, view_angle_2) && std::find(out_vecs.begin(), out_vecs.end(), chunk_coord(x0 + y, y0 + x)) == out_vecs.end())
			{
				out_vecs.push_back(chunk_coord(x0 + y, y0 + x));
			}
			if (between_angles(-y, x, view_angle_1, view_angle_2) && std::find(out_vecs.begin(), out_vecs.end(), chunk_coord(x0 - y, y0 + x)) == out_vecs.end())
			{
				out_vecs.push_back(chunk_coord(x0 - y, y0 + x));
			}
			if (between_angles(-x, y, view_angle_1, view_angle_2) && std::find(out_vecs.begin(), out_vecs.end(), chunk_coord(x0 - x, y0 + y)) == out_vecs.end())
			{
				out_vecs.push_back(chunk_coord(x0 - x, y0 + y));
			}
			if (between_angles(-x, -y, view_angle_1, view_angle_2) && std::find(out_vecs.begin(), out_vecs.end(), chunk_coord(x0 - x, y0 - y)) == out_vecs.end())
			{
				out_vecs.push_back(chunk_coord(x0 - x, y0 - y));
			}
			if (between_angles(-y, -x, view_angle_1, view_angle_2) && std::find(out_vecs.begin(), out_vecs.end(), chunk_coord(x0 - y, y0 - x)) == out_vecs.end())
			{
				out_vecs.push_back(chunk_coord(x0 - y, y0 - x));
			}
			if (between_angles(y, -x, view_angle_1, view_angle_2) && std::find(out_vecs.begin(), out_vecs.end(), chunk_coord(x0 + y, y0 - x)) == out_vecs.end())
			{
				out_vecs.push_back(chunk_coord(x0 + y, y0 - x));
			}
			if (between_angles(x, -y, view_angle_1, view_angle_2) && std::find(out_vecs.begin(), out_vecs.end(), chunk_coord(x0 - y, y0 + x)) == out_vecs.end())
			{
				out_vecs.push_back(chunk_coord(x0 + x, y0 - y));
			}

			if (err <= 0)
			{
				y += 1;
				err += 2 * y + 1;
			}
			if (err > 0)
			{
				x -= 1;
				err -= 2 * x + 1;
			}
		}
	}
	return out_vecs;
}

int TGLChunkSpawn::get_point(int x, int y, int z)
{
	if (!test_chunk)
	{
		return block_generator->get_point(x, y, z);
	}
	else
	{
		if (z == 180)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
}

unsigned char * TGLChunkSpawn::get_points(int x, int y, int division)
{
	return block_generator->get_points((x), (y), 0, division);
}