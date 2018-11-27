#ifndef _TMCPlayer
#define _TMCPlayer

#include "TGLChunkSpawn.h"

class TMCPlayer : public TGLPlayer
{
    TGLChunkSpawn * chunk_spawn;
    static double max_hit_distance = 5;
    static int inventory_slot_width = 120;
    static int inventory_slot_height = 120;
    static int inventory_slot_border = 10;
    static int inventory_screen_pos_x = 100;
    static int inventory_screen_pos_y = 100;
    glm::vec3 equipped_border_color;
    glm::vec3 unequipped_border_color;
    
public:
    TMCPlayer();
    void init_inventory(int num_slots);
    void tick(double time_delta);
    void set_chunk_spawn(TGLChunkSpawn * in_chunk_spawn);
    void add_quick_slot();
};

#endif