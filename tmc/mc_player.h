#ifndef TMC_PLAYER_H_
#define TMC_PLAYER_H_

#include <vector>

#include "tgl/player.h"
#include "tmc/chunk_spawn.h"
#include "tmc/hud/crafting_table_hud.h"
#include "tmc/hud/inventory_slot_group.h"

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
#ifdef _TGL_CLIENT
	tgl::HudElement * hud_dragging;
	tmc::hud::CraftingTableHud * crafting_table_hud;
#endif  // _TGL_CLIENT
	bool crafting_table_on;
	glm::vec2 orig_drag_pos;
	glm::vec2 drag_mouse_diff;
	int dragged_inventory_index;

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
	int screen_pos_to_inventory_index(int in_pos_x, int in_pos_y, 
									  int &inventory_index, tgl::HudElement *& out_hud_element);
};

} // namespace tmc

#endif