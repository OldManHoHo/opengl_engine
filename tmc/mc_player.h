#ifndef TMC_PLAYER_H_
#define TMC_PLAYER_H_

#include <vector>

#include "tmc/chunk_spawn.h"
#include "tgl/player.h"

namespace tmc
{

class Player : public tgl::Player
{
    tmc::ChunkSpawn * chunk_spawn;
    glm::vec3 equipped_border_color;
    glm::vec3 unequipped_border_color;
    std::vector<glm::vec3> hits;
    std::vector<std::pair<glm::vec3, e_block_type>> placements;
    bool inventory_on;
    int inventory_slots;
    int quick_use_slots;

 public:
    static const int max_hit_distance = 5;
    static const int inventory_slot_width = 120;
    static const int inventory_slot_height = 120;
    static const int inventory_slot_border = 10;
    static const int inventory_screen_pos_x = 100;
    static const int inventory_screen_pos_y = 100;
    static const int space_between_quick_full = 100;
    static const int item_collect_radius = 2;
    static const int full_inventory_slot_width = 6;
    static const int full_inventory_slot_height = 6;
    
 public:
    Player();
    void init_inventory(int num_slots);
    void tick(double time_delta);
    void set_chunk_spawn(tmc::ChunkSpawn * in_chunk_spawn);
    void add_quick_slot();
    std::vector<glm::vec3> fetch_hits();
    std::vector<std::pair<glm::vec3, e_block_type>> fetch_placements();
};

} // namespace tmc

#endif