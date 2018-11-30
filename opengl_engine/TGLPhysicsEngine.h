#pragma once
#ifndef _TGL_PHYSICSENGINE
#define _TGL_PHYSICSENGINE

#include <vector>

#include "TGLActor.h"
#include "TGLChunkSpawn.h"




class TGLPhysicsEngine
{
public:
	TGLPhysicsEngine();
	~TGLPhysicsEngine();

	void tick(double time_delta, std::vector <TGLActor*> const & actors, TGLChunkSpawn * chunks_spawner);
	std::vector <glm::vec3> get_world_blocks(TGLActor * in_actor, TGLChunkSpawn * chunks_spawner);
	void collide_aligned_block_and_block(TGLActor * in_actor, glm::vec3 in_block);
	void move(double time_delta, TGLActor * in_player, std::vector <glm::vec3>  in_blocks);
	void collide_aligned_block_and_block2(TGLActor * in_actor, glm::vec3 in_block);
	void collide_cylinder_and_block(TGLActor * in_actor, glm::vec3 in_block);

	FILE * out_file;
};

#endif