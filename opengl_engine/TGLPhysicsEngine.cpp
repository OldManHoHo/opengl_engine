#include "TGLPhysicsEngine.h"
#include "TGLBounds.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

template <typename T> int sign(T val) {
	return (T(0) < val) - (val < T(0));
}

double clamp(double value, double min, double max)
{
	if (value < min)
	{
		return min;
	}
	if (value > max)
	{
		return max;
	}
	return value;
}

TGLPhysicsEngine::TGLPhysicsEngine()
{

	//fopen(&out_file, "test.text", "a");

}


TGLPhysicsEngine::~TGLPhysicsEngine()
{
}

void TGLPhysicsEngine::tick(double time_delta, std::vector <TGLActor*> const & actors, TGLChunkSpawn * chunks_spawner)
{
	for (auto it = actors.begin(); it != actors.end(); ++it)
	{
		if ((*it)->get_bounds() != nullptr)
		{
			if((*it)->mass > 0)
			{
				
				//std::ofstream out_file;
				//out_file.open("test.txt", std::ios::app);
				
				(*it)->set_on_ground(false);
				(*it)->vel += float(time_delta)*(*it)->accel + float(time_delta*9.81)*glm::vec3(0, -1.0, 0);
				std::vector <glm::vec3> collision_blocks = get_world_blocks((*it), chunks_spawner);
				move(time_delta, (*it), collision_blocks);
				/*
				
				for (auto block_it = collision_blocks.begin(); block_it != collision_blocks.end(); ++block_it)
				{
					//collide_cylinder_and_block((*it), (*block_it));
					collide_aligned_block_and_block2((*it), (*block_it));
				}
				(*it)->prev_pos = (*it)->pos;
				(*it)->pos += float(time_delta)*(*it)->vel;
				(*it)->vel += float(time_delta)*(*it)->accel + float(time_delta*9.81)*glm::vec3(0, -1.0, 0);
				//fprintf(out_file,"velocity: %f,%f,%f\n", (*it)->vel.y, (*it)->pos.y, time_delta);
				//out_file << "velocity:" << (*it)->vel.y << ", " << time_delta << "\n";
				//out_file.close();
				//fclose(out_file);
				*/
			}
		}
	}
}

std::vector <glm::vec3> TGLPhysicsEngine::get_world_blocks(TGLActor * in_actor, TGLChunkSpawn * chunks_spawner)
{
	glm::vec3 position = in_actor->get_pos();

	TGLBlockBounds * actor_bounds = (TGLBlockBounds*)(in_actor->get_bounds());
	std::vector <glm::vec3> out_points;

	int x[3];
	int y[5];
	int z[3];
	x[0] = int(position.x);
	x[1] = int(position.x + (actor_bounds)->width + 0.5);
	x[2] = int(position.x - ((actor_bounds)->width + 0.5));

	y[0] = int(position.y);
	y[1] = int(position.y + (actor_bounds)->height/2.0 + 0.5);
	y[2] = int(position.y - ((actor_bounds)->height/2.0 + 0.5));

	z[0] = int(position.z);
	z[1] = int(position.z + (actor_bounds)->depth/2.0 + 0.5);
	z[2] = int(position.z - ((actor_bounds)->depth + 0.5));

	x[0] = int(position.x);
	x[1] = int(position.x)-1;
	x[2] = int(position.x)+1;

	y[0] = int(position.y);
	y[1] = int(position.y) - 1;
	y[2] = int(position.y) + 1;
	y[3] = int(position.y) - 2;
	y[4] = int(position.y) + 2;

	z[0] = int(position.z);
	z[1] = int(position.z)-1;
	z[2] = int(position.z)+1;

	x[0] = floor(position.x - (actor_bounds)->width/2.0);
	x[1] = floor(position.x + (actor_bounds)->width/2.0);
	x[0] = int(round(position.x));
	x[1] = int(round(position.x)) - 1;
	x[2] = int(round(position.x)) + 1;

	y[0] = int(round(position.y));
	y[1] = int(round(position.y)) - 1;
	y[2] = int(round(position.y)) + 1;
	y[3] = int(round(position.y)) - 2;
	y[4] = int(round(position.y)) + 2;

	z[0] = floor(position.z - (actor_bounds)->depth / 2.0);
	z[1] = floor(position.z + (actor_bounds)->depth / 2.0);
	z[2] = int(round(position.z)) + 1;
	z[0] = int(round(position.z));
	z[1] = int(round(position.z)) - 1;
	z[2] = int(round(position.z)) + 1;


	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				e_block_type block_type = chunks_spawner->get_point(x[i], z[k],y[j]);
				
				if (block_type != bt_air)
				{
					out_points.push_back(glm::vec3(x[i], y[j], z[k]));
					
					//out_points.push_back(glm::vec3(x[i], 175, z[k]));
				}
				
			}
		}
	}
	return out_points;
	int counter = 256;
	//unsigned char * block_type = chunks_spawner->get_points(16*int(int(position.x / 16)) - 1, 16 * int(int(position.z/16)) - 1, 18);
	while (1)
	{
		int block_type = chunks_spawner->get_point( -int(position.x), -int(position.z), 0);
		if (block_type)
		{
			//in_actor->pos.y = block_type + 2;
			//in_actor->vel.y = 0;
			break;
		}
	}

	return out_points;
}

void TGLPhysicsEngine::move(double time_delta, TGLActor * in_actor, std::vector <glm::vec3>  in_blocks)
{
	TGLBlockBounds * actor_bounds = (TGLBlockBounds*)(in_actor->get_bounds());
	double block_height = 1.0;
	double block_width = 1.0;
	double block_depth = 1.0;
	double pen;




	in_actor->pos.x += in_actor->vel.x*time_delta;

	for (auto in_block : in_blocks)
	{
		double y_pen = -abs(in_actor->pos.y - in_block.y) + (actor_bounds->height / 2.0 + block_height / 2.0);
		double x_pen = -abs(in_actor->pos.x - in_block.x) + (actor_bounds->width / 2.0 + block_width / 2.0);
		double z_pen = -abs(in_actor->pos.z - in_block.z) + (actor_bounds->depth / 2.0 + block_depth / 2.0);
		if (y_pen > 0 && x_pen > 0 && z_pen > 0)
		{
			in_actor->pos.x -= x_pen*sign(in_actor->vel.x)*1.01;
			in_actor->vel.x = 0;
		}
	}

	in_actor->pos.z += in_actor->vel.z*time_delta;

	for (auto in_block : in_blocks)
	{
		double y_pen = -abs(in_actor->pos.y - in_block.y) + (actor_bounds->height / 2.0 + block_height / 2.0);
		double x_pen = -abs(in_actor->pos.x - in_block.x) + (actor_bounds->width / 2.0 + block_width / 2.0);
		double z_pen = -abs(in_actor->pos.z - in_block.z) + (actor_bounds->depth / 2.0 + block_depth / 2.0);
		if (y_pen > 0 && x_pen > 0 && z_pen > 0)
		{
			in_actor->pos.z -= z_pen*sign(in_actor->vel.z)*1.01;
			in_actor->vel.z = 0;
		}
	}

	in_actor->pos.y += in_actor->vel.y*time_delta;

	for (auto in_block : in_blocks)
	{
		double y_pen = -abs(in_actor->pos.y - in_block.y) + (actor_bounds->height / 2.0 + block_height / 2.0);
		double x_pen = -abs(in_actor->pos.x - in_block.x) + (actor_bounds->width / 2.0 + block_width / 2.0);
		double z_pen = -abs(in_actor->pos.z - in_block.z) + (actor_bounds->depth / 2.0 + block_depth / 2.0);
		if (y_pen > 0 && x_pen > 0 && z_pen > 0)
		{
			in_actor->pos.y -= y_pen*sign(in_actor->vel.y)*1.01;
			in_actor->vel.y = 0;
			in_actor->set_on_ground(true);
		}
	}

}

void TGLPhysicsEngine::collide_aligned_block_and_block2(TGLActor * in_actor, glm::vec3 in_block)
{
	glm::vec3 normal = in_block - in_actor->get_pos();
	TGLBlockBounds * actor_bounds = (TGLBlockBounds*)(in_actor->get_bounds());
	double block_height = 1.0;
	double block_width = 1.0;
	double block_depth = 1.0;
	double y_pen = -abs(in_actor->pos.y - in_block.y) + (actor_bounds->height / 2.0 + block_height / 2.0);
	double x_pen = -abs(in_actor->pos.x - in_block.x) + (actor_bounds->width / 2.0 + block_width / 2.0);
	double z_pen = -abs(in_actor->pos.z - in_block.z) + (actor_bounds->depth / 2.0 + block_depth / 2.0);
	double pen;

	if (y_pen > 0 && x_pen > 0 && z_pen > 0)
	{
		// Collision detected
		glm::vec3 collision_pos_1 = in_actor->vel*abs(float(y_pen / in_actor->vel.y));
		glm::vec3 collision_pos_2 = in_actor->vel*abs(float(x_pen / in_actor->vel.x));
		glm::vec3 collision_pos_3 = in_actor->vel*abs(float(z_pen / in_actor->vel.z));
		glm::vec3 collision_pos;
		double l1 = glm::length(collision_pos_1);
		double l2 = glm::length(collision_pos_2);
		double l3 = glm::length(collision_pos_3);

		float proj_vel;

		if ((l1 < l3 || glm::isnan(l3))  && (l1 < l2 || glm::isnan(l2)))
		{
			if (in_actor->vel.y < 0)
			{
				normal = glm::vec3(0, -1, 0);
			}
			else
			{
				normal = glm::vec3(0, 1, 0);
			}
			collision_pos = collision_pos_1;
			pen = y_pen;
		}
		else if ((l2 < l3 || glm::isnan(l3)) && (l2 < l1 || glm::isnan(l1)))
		{
			if (in_actor->vel.x < 0)
			{
				normal = glm::vec3(-1, 0, 0);
			}
			else
			{
				normal = glm::vec3(1, 0, 0);
			}
			collision_pos = collision_pos_2;
			pen = x_pen;
		}
		else if ((l3 < l2 || glm::isnan(l2)) && (l3 < l1 || glm::isnan(l1)))
		{
			if (in_actor->vel.z < 0)
			{
				normal = glm::vec3(0, 0, -1);
			}
			else
			{
				normal = glm::vec3(0, 0, 1);
			}
			collision_pos = collision_pos_3;
			pen = z_pen;
		}
		if (!glm::isnan(collision_pos).x && !glm::isnan(collision_pos).y && !glm::isnan(collision_pos).z)
		{
			proj_vel = glm::dot(in_actor->vel, normal);
			in_actor->vel -= normal*proj_vel;
			//in_actor->pos = in_actor->pos - collision_pos*1.00f;
			in_actor->pos = in_actor->pos - normal*float(pen);
		}
		else
		{
			printf("FAKE\n");
		}
	}
}

void TGLPhysicsEngine::collide_aligned_block_and_block(TGLActor * in_actor, glm::vec3 in_block)
{
	TGLBlockBounds * actor_bounds = (TGLBlockBounds*)(in_actor->get_bounds());
	double block_height = 1.0;
	double block_width = 1.0;
	double block_depth = 1.0;
	
	while (abs(in_actor->pos.y - in_block.y) < actor_bounds->height / 2.0 + block_height / 2.0 && abs(in_actor->pos.x - in_block.x) < actor_bounds->width / 2.0 + block_width / 2.0 && abs(in_actor->pos.z - in_block.z) < actor_bounds->depth / 2.0 + block_depth / 2.0)
	{

		// Collision found


		//if (in_actor->vel.y != 0 || in_actor->vel.x != 0 || in_actor->vel.z != 0)
		{
			double t = 0, tx1 = 0, tx2 = 0, ty1 = 0, ty2 = 0, tz1 = 0, tz2 = 0;

			if (in_actor->vel.y != 0)
			{
				//ty1 = (actor_bounds->height / 2.0 + block_height / 2.0 + in_block.y - in_actor->pos.y) / (in_actor->vel.y);
				//ty2 = (-actor_bounds->height / 2.0 - block_height / 2.0 + in_block.y - in_actor->pos.y) / (in_actor->vel.y);
				ty1 = (in_actor->pos.y - in_block.y - (actor_bounds->height / 2.0 + block_height / 2.0)) / in_actor->vel.y;
				ty2 = (in_actor->pos.y - in_block.y - (actor_bounds->height / 2.0 + block_height / 2.0)) / in_actor->vel.y;
			}
			else
			{
				ty1 = 0;
				ty2 = (in_actor->pos.y - in_block.y - (actor_bounds->height / 2.0 + block_height / 2.0));
				if (ty2 > 0)
				{
					if (in_actor->pos.y - in_actor->prev_pos.y > 0)
						in_actor->pos.y -= ty2;
					else
						in_actor->pos.y -= ty2;
				}
			}
			if (ty2 > 0)
			{
				double prev_y = in_actor->pos.y;
				if (abs(ty2*(-in_actor->vel.y)) > 0.6)
				{
					in_actor->pos.y = in_actor->prev_pos.y;
					in_actor->vel.y = 0;
				}
				else
				{
					in_actor->pos.y += 1.05*ty2*(-in_actor->vel.y);
					in_actor->vel.y = 0;
					in_actor->set_on_ground(true);
					if (abs(prev_y - in_actor->pos.y) > 0.9)
					{
						std::cout << "TEST" << "\n";
					}
				}
				continue;
			}
			if (in_actor->vel.x != 0)
			{
				//tx1 = (actor_bounds->width / 2.0 + block_width / 2.0 + in_block.x - in_actor->pos.x) / (in_actor->vel.x);
				//tx2 = (-actor_bounds->width / 2.0 - block_width / 2.0 + in_block.x - in_actor->pos.x) / (in_actor->vel.x);
				tx1 = (in_actor->pos.x - in_block.x - (actor_bounds->width / 2.0 + block_width / 2.0)) / -in_actor->vel.x;
				tx2 = ((actor_bounds->width / 2.0 + block_width / 2.0) - abs(in_actor->pos.x - in_block.x)) / abs(in_actor->vel.x);
			}
			else
			{
				tx1 = 0;
				tx2 = ((actor_bounds->width / 2.0 + block_width / 2.0) - abs(in_actor->pos.x - in_block.x));
				if (tx2 > 0)
				{
					if (in_actor->pos.x - in_actor->prev_pos.x > 0)
						in_actor->pos.x -= tx2;
					else
						in_actor->pos.x -= tx2;
				}
			}
			if (tx2 > 0)
			{
				if (abs(in_actor->pos.x + tx2*(-in_actor->vel.x) - in_actor->pos.x) > 0.6)
				{
					std::cout << "dx: " << in_actor->pos.x + tx2*(-in_actor->vel.x) - in_actor->pos.x << "\n";
				}
				double prev_x = in_actor->pos.x;
				if (abs(tx2*(-in_actor->vel.x)) > 0.6)
				{
					in_actor->pos.x = in_actor->prev_pos.x;
					in_actor->vel.x = 0;
				}
				else
				{
					in_actor->pos.x += 1.05*tx2*(-in_actor->vel.x);
					in_actor->vel.x = 0;
				}
				continue;
			}
			if (in_actor->vel.z != 0)
			{
				//tz1 = (actor_bounds->depth / 2.0 + block_depth / 2.0 + in_block.z - in_actor->pos.z) / (in_actor->vel.z);
				//tz2 = (-actor_bounds->depth / 2.0 - block_depth / 2.0 + in_block.z - in_actor->pos.z) / (in_actor->vel.z);
				tz1 = (in_actor->pos.z - in_block.z - (actor_bounds->depth / 2.0 + block_depth / 2.0)) / -in_actor->vel.z;
				tz2 = ((actor_bounds->depth / 2.0 + block_depth / 2.0) - abs(in_actor->pos.z - in_block.z)) / abs(in_actor->vel.z);
			}
			else
			{
				tz1 = 0;
				tz2 = ((actor_bounds->depth / 2.0 + block_depth / 2.0) - abs(in_actor->pos.z - in_block.z));
				if (tz2 > 0)
				{
					if (in_actor->pos.z - in_actor->prev_pos.z > 0)
						in_actor->pos.z -= tz2;
					else
						in_actor->pos.z -= tz2;
				}
			}
			if (tz2 > 0)
			{
				if (abs(tz2*(-in_actor->vel.z)) > 0.6)
				{
					in_actor->pos.z = in_actor->prev_pos.z;
					in_actor->vel.z = 0;
				}
				else
				{
					in_actor->pos.z += 1.05*tz2*(-in_actor->vel.z);
					in_actor->vel.z = 0;
					std::cout << "t: " << tz2 << "\n";
				}
				continue;
			}
			/*
			t = 10000;
			//if (tx1 > 0) { t = tx1; }
			if (tx2 > 0 && tx2 < t) { t = tx2; }
			//if (ty1 > 0 && ty1 < t) { t = ty1; }
			if (ty2 > 0 && ty2 < t) { t = ty2; }
			//if (tz1 > 0 && tz1 < t) { t = tz1; }
			if (tz2 > 0 && tz2 < t) { t = tz2; }
			*/



		}

	}
}

void TGLPhysicsEngine::collide_cylinder_and_block(TGLActor * in_actor, glm::vec3 in_block)
{
	TGLCylinderBounds * actor_bounds = (TGLCylinderBounds*)(in_actor->get_bounds());
	glm::vec3 m_3d = in_actor->pos - in_actor->prev_pos;
	glm::vec2 m_raw = glm::vec2(m_3d.x, m_3d.z);
	glm::vec2 m = glm::normalize(m_raw);
	glm::vec2 c1 = glm::vec2(in_actor->pos.x, in_actor->pos.z);
	glm::vec2 normal(0, 0);
	float r = actor_bounds->radius;
	glm::vec2 N;
	glm::vec2 c2_tmp;
	float k, k1, k2;
	float distance = glm::length(m_raw);

	float bb = in_block.z - 0.5;
	float bt = in_block.z + 0.5;
	float bl = in_block.x - 0.5;
	float br = in_block.x + 0.5;

	k = distance;

	N.y = bb;
	float a = (c1.y - N.y) / m.y;
	N.x = c1.x - a*m.x;

	k1 = glm::dot(m, c1 - N) + sqrt(pow(glm::dot(m, c1 - N), 2) - (glm::dot(c1 - N, c1 - N) - r*r));
	if (k1 > 0 && k1 < k)
	{
		k = k1;
		normal = glm::vec2(0, -1);
	}
	k1 = glm::dot(m, c1 - N) - sqrt(pow(glm::dot(m, c1 - N), 2) - (glm::dot(c1 - N, c1 - N) - r*r));
	if (k1 > 0 && k1 < k)
	{
		k = k1;
		normal = glm::vec2(0, -1);
	}
	

	N.y = bt;
	a = (c1.y - N.y) / m.y;
	N.x = c1.x - a*m.x;

	k1 = glm::dot(m, c1 - N) + sqrt(pow(glm::dot(m, c1 - N), 2) - (glm::dot(c1 - N, c1 - N) - r*r));
	if (k1 > 0 && k1 < k)
	{
		k = k1;
		normal = glm::vec2(0, 1);
	}
	k1 = glm::dot(m, c1 - N) - sqrt(pow(glm::dot(m, c1 - N), 2) - (glm::dot(c1 - N, c1 - N) - r*r));
	if (k1 > 0 && k1 < k)
	{
		k = k1;
		normal = glm::vec2(0, 1);
	}

	N.y = bl;
	a = (c1.y - N.y) / m.y;
	N.x = c1.x - a*m.x;

	k1 = glm::dot(m, c1 - N) + sqrt(pow(glm::dot(m, c1 - N), 2) - (glm::dot(c1 - N, c1 - N) - r*r));
	if (k1 > 0 && k1 < k)
	{
		k = k1;
		normal = glm::vec2(-1, 0);
	}
	k1 = glm::dot(m, c1 - N) - sqrt(pow(glm::dot(m, c1 - N), 2) - (glm::dot(c1 - N, c1 - N) - r*r));
	if (k1 > 0 && k1 < k)
	{
		k = k1;
		normal = glm::vec2(-1, 0);
	}

	N.y = br;
	a = (c1.y - N.y) / m.y;
	N.x = c1.x - a*m.x;

	k1 = glm::dot(m, c1 - N) + sqrt(pow(glm::dot(m, c1 - N), 2) - (glm::dot(c1 - N, c1 - N) - r*r));
	if (k1 > 0 && k1 < k)
	{
		k = k1;
		normal = glm::vec2(1, 0);
	}
	k1 = glm::dot(m, c1 - N) - sqrt(pow(glm::dot(m, c1 - N), 2) - (glm::dot(c1 - N, c1 - N) - r*r));
	if (k1 > 0 && k1 < k)
	{
		k = k1;
		normal = glm::vec2(1, 0);
	}

	//float scale = k / distance;
	glm::vec3 m_3d_n = glm::normalize(m_3d);
	glm::vec3 corrected = in_actor->pos - k*glm::normalize(m_3d);

	if ((in_actor->pos.y - actor_bounds->height / 2.0 < in_block.y + 0.5 && in_actor->pos.y - actor_bounds->height / 2.0 > in_block.y - 0.5) || (in_actor->pos.y + actor_bounds->height / 2.0 > in_block.y - 0.5 && in_actor->pos.y + actor_bounds->height / 2.0 < in_block.y + 0.5))
	{
		if (m_3d.y > 0 && (corrected.y + actor_bounds->height / 2.0 < in_block.y - 0.5 || k == 0))
		{
			glm::vec3 y_correction = m_3d_n*float((in_actor->pos.y + actor_bounds->height / 2.0 - (in_block.y - 0.5)) / m_3d_n.y);
			in_actor->pos -= y_correction*1.005f;
			in_actor->vel.y = 0;
		}
		else if (m_3d.y < 0 && (corrected.y - actor_bounds->height / 2.0 > in_block.y + 0.5 || k == 0))
		{
			glm::vec3 y_correction = m_3d_n*float((in_actor->pos.y - actor_bounds->height / 2.0 - (in_block.y + 0.5)) / m_3d_n.y);
			in_actor->pos -= y_correction*1.005f;
			in_actor->vel.y = 0.1;
			printf("Y Pos: %f\n", in_actor->pos.y);
		}
		else
		{
			if (abs(corrected.y - actor_bounds->height / 2.0 - (in_block.y + 0.5)) < 0.01)
			{
				corrected = in_actor->pos;
				corrected.y = in_block.y + 0.5 + 0.01 + actor_bounds->height / 2.0;
				printf("Corrected y: %f\n", in_actor->pos.y);
			}
			in_actor->pos = corrected;
			printf("Y Pos horiz: %f\n", in_actor->pos.y);
		}
	}



}