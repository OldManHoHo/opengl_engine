#pragma once
#ifndef TGL_PHYSICSENGINE_H_
#define TGL_PHYSICSENGINE_H_

#include <vector>

#include "tgl/actor.h"
#include "tmc/chunk_spawn.h"

namespace tgl
{

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void tick(double time_delta, std::vector <tgl::Actor*> const & actors, tmc::ChunkSpawn * chunks_spawner, bool gravity_enabled = true);
	std::vector <glm::vec3> get_world_blocks(tgl::Actor * in_actor, tmc::ChunkSpawn * chunks_spawner);
	void collide_aligned_block_and_block(tgl::Actor * in_actor, glm::vec3 in_block);
	void move(double time_delta, tgl::Actor * in_player, std::vector <glm::vec3>  in_blocks, double in_speed_mult);
	void collide_aligned_block_and_block2(tgl::Actor * in_actor, glm::vec3 in_block);
	void collide_cylinder_and_block(tgl::Actor * in_actor, glm::vec3 in_block);

	FILE * out_file;
};

} // namespace tgl

#endif