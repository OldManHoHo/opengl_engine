#ifndef TMC_MC_INTERACTION_MANAGER_H_
#define TMC_MC_INTERACTION_MANAGER_H_

#include "tgl/interaction_manager.h"
#include "tmc/chunk_spawn.h"
#include "tmc/mc_player.h"

namespace tmc
{

class InteractionManager
{
    tmc::ChunkSpawn * chunk_spawn;
 public:
    void tick(double time_delta, std::vector <std::unique_ptr<tgl::Actor>>& actors);
};

}  // namespace tmc

#endif  // TMC_MC_INTERACTION_MANAGER_H_