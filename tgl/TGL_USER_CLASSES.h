#ifndef TGL_USER_CLASSES_H_
#define TGL_USER_CLASSES_H_

#include "tmc/mc_player.h"
#define USER_PLAYER_CLASS tmc::Player

#include "tmc/chunk_spawn.h"
#define USER_WORLD_CLASS tmc::ChunkSpawn

#include "tgl/physics_engine.h"
#define USER_PHYSICS_CLASS tgl::PhysicsEngine

#include "tmc/mc_interaction_manager.h"
#define USER_INTERACTION_MANAGER_CLASS tmc::InteractionManager

#endif