#ifndef TMC_PLAYER_H_
#define TMC_PLAYER_H_

#include <vector>

#include "tgl/player.h"
#include "tmc/chunk_spawn.h"

namespace tmc
{

class Player : public tgl::Player
{
    tmc::ChunkSpawn * chunk_spawn;
    static const int max_hit_distance = 5;
    static const int inventory_slot_width = 120;
    static const int inventory_slot_height = 120;
    static const int inventory_slot_border = 10;
    static const int inventory_screen_pos_x = 100;
    static const int inventory_screen_pos_y = 100;
	static const int item_collect_radius = 2;
    glm::vec3 equipped_border_color;
    glm::vec3 unequipped_border_color;
    
public:
    Player();
    void init_inventory(int num_slots);
    void tick(double time_delta);
    void set_chunk_spawn(tmc::ChunkSpawn * in_chunk_spawn);
    void add_quick_slot();
};

} // namespace tmc

#endif