#include "tmc/mc_player.h"
#include "tgl/useful_structures.h"

namespace tmc
{

Player::Player():
    chunk_spawn(nullptr),
    equipped_border_color(0.4, 0.4, 0.4),
    unequipped_border_color(0.2, 0.2, 0.2)
{
    init_inventory(inventory.default_quick_use_size);
}

void Player::init_inventory(int num_slots)
{
#ifdef _TGL_CLIENT
    inventory_hud =
        new tgl::HudElement(inventory_slot_width*num_slots,
                            inventory_slot_height,
                            glm::vec2(inventory_screen_pos_x,
                                      inventory_screen_pos_y),
                            glm::vec3(0.0, 0.0, 0.0));
#endif
    int offset = inventory_slot_border;
    int shift = inventory_slot_width;
#ifdef _TGL_CLIENT
    for (int i = 0; i < num_slots; ++i)
    {
        tgl::HudElement * inventory_itemb =
            new tgl::HudElement(inventory_slot_width,
                    inventory_slot_height,
                    glm::vec2(i*inventory_slot_width, 0),
                    glm::vec3(0.5, 0.5, 0.5));
        tgl::HudElement * inventory_item =
            new tgl::HudElement(inventory_slot_width - 2*inventory_slot_border,
                    inventory_slot_height - 2*inventory_slot_border,
                    glm::vec2(i*inventory_slot_width + inventory_slot_border,
                    inventory_slot_border), glm::vec3(0.5, 0.5, 0.5),
                    "content/textures/mc.png");

        inventory_hud->sub_elements.push_back(inventory_itemb);
        inventory_hud->sub_elements.push_back(inventory_item);
    }
    add_hud(inventory_hud);
#endif
}

extern tgl::Actor debug_actor;

void Player::tick(double time_delta)
{
    tgl::Player::tick(time_delta);

    static double time_since_last_left = 10;
    static double time_since_last_right = 10;
    time_since_last_left += time_delta;
    time_since_last_right += time_delta;
    if (input_handler.key_states[1])
    {
        std::cout << "MOUSE 1" << "\n";
        if (time_since_last_left >= multi_press_threshold)
        {
            glm::vec3 forward_vector(1.0, 0.0, 0.0);

            forward_vector = glm::mat3(get_rot())*forward_vector;
            // forward_vector += pos;
            // forward_vector += glm::vec3(0.0, 0.5, 0);
            
            // TODO(Teddy Walsh): hit should include direction and pos info
            set_hitting(forward_vector);
            tgl::InventoryItem& check = get_equipped();
            if (check.type != tgl::ItemId::none)
            {
// #ifdef _TGL_SERVER
                hits.push_back(forward_vector);
// #endif  // _TGL_SERVER
            }
            time_since_last_left = 0;
        }
    }
    if (input_handler.key_states[2])
    {
        if (time_since_last_right >= multi_press_threshold)
        {
            glm::vec3 forward_vector(1.0, 0.0, 0.0);
            forward_vector = glm::mat3(get_rot())*forward_vector;
            // forward_vector += pos;
            // forward_vector += glm::vec3(0.0, 0.5, 0);

            set_hitting(forward_vector);
            e_block_type hit_type;
            glm::vec3 block_to_add;
            glm::vec3 intersect_point;
            glm::vec3 hit_block =
                chunk_spawn->get_block_pointed_at(eye_loc,
                                                  forward_vector,
                                                  max_hit_distance,
                                                  hit_type,
                                                  block_to_add,
                                                  intersect_point);

            if (chunk_spawn != nullptr)
            {
                tgl::InventoryItem& check = get_equipped();
                if (check.type != tgl::ItemId::none)
                {
                    e_block_type type_to_add =
                        item_id_to_block_type(get_equipped().type);
                    if (type_to_add != bt_invalid)
                    {
                        chunk_spawn->post_placement(block_def(block_to_add.x,
                                                              block_to_add.y,
                                                              block_to_add.z,
                                                              type_to_add));
                        change_inventory_amount(get_equipped().type, -1);
                    }
                }
            }
        }
        time_since_last_right = 0;
    }
#ifdef _TGL_CLIENT
    for (int i = 0; i < inventory.default_quick_use_size; ++i)
    {
        if (input_handler.key_states['1' + i])
        {
            equipped_item = inventory.get_item(i, 0);
            equipped_index = i;
        }
    }
    for (int i = 0; i < inventory.default_quick_use_size; ++i)
    {
        if (i == equipped_index)
        {
            inventory_hud->sub_elements[2*i]->color = equipped_border_color;
            // hud[0]->sub_elements[2*i]->color = equipped_border_color;
        }
        else
        {
            inventory_hud->sub_elements[2 * i]->color = unequipped_border_color;
        }
        tgl::InventoryItem * next_item = inventory.get_item(i, 0);
        int index = i*2 + 1;
        if (next_item != nullptr)
        {
            inventory_hud->sub_elements[index]->set_offsets(
                tgl::useful_structures::
                    item_id_to_texture_coords[next_item->type],
                tgl::useful_structures::
                    item_id_to_texture_coords[next_item->type] +
                    glm::vec2(16, 16));
        }
        else
        {
            inventory_hud->sub_elements[index]->set_offsets(
                glm::vec2(16, 8 * 16),
                glm::vec2(16, 8 * 16) + glm::vec2(16, 16));
        }
    }
#else
    equipped_item = inventory.get_item(equipped_index, 0);
#endif
}

void Player::set_chunk_spawn(tmc::ChunkSpawn * in_chunk_spawn)
{
    chunk_spawn = in_chunk_spawn;
}

void Player::add_quick_slot()
{
}

std::vector<glm::vec3> Player::fetch_hits()
{
    std::vector<glm::vec3> out_hits = hits;
    hits.clear();
    return out_hits;
}

std::vector<std::pair<glm::vec3, e_block_type>> Player::fetch_placements()
{
    std::vector<std::pair<glm::vec3, e_block_type>> out_placements = placements;
    placements.clear();
    return out_placements;
}

}  // namespace tmc
