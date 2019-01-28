#include "tmc/mc_player.h"

#include "tgl/globals.h"
#include "tgl/inventory.h"
#include "tgl/useful_structures.h"
#include "tmc/hud/inventory_slot.h"


namespace tmc
{

Player::Player():
    chunk_spawn(nullptr),
    equipped_border_color(0.4, 0.4, 0.4),
    unequipped_border_color(0.2, 0.2, 0.2),
    inventory_on(false),
    inventory_slots(full_inventory_slot_width*full_inventory_slot_height
            + tgl::Inventory::default_quick_use_size),
    quick_use_slots(tgl::Inventory::default_quick_use_size),
    tgl::Player(full_inventory_slot_width*full_inventory_slot_height
                + tgl::Inventory::default_quick_use_size),
	crafting_table_hud(nullptr),
	crafting_table_on(false)
{
    init_inventory(quick_use_slots);
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
    tmc::hud::InventorySlotGroup * inventory_hud_slot_group = 
        new tmc::hud::InventorySlotGroup(inventory_screen_pos_x,
            inventory_screen_pos_y + 
                inventory_slot_height + 
                space_between_quick_full,
            full_inventory_slot_height*full_inventory_slot_width, 
            full_inventory_slot_width,
            inventory_slot_width,
            inventory_slot_height,
            inventory_slot_border);
    full_inventory_hud = static_cast<tgl::HudElement*>(inventory_hud_slot_group);

    tmc::hud::InventorySlotGroup * quick_use_hud_slot_group =
        new tmc::hud::InventorySlotGroup(inventory_screen_pos_x,
            inventory_screen_pos_y,
            quick_use_slots,
            quick_use_slots,
            inventory_slot_width,
            inventory_slot_height,
            inventory_slot_border);
    inventory_hud = static_cast<tgl::HudElement*>(quick_use_hud_slot_group);
	crafting_table_hud =
		new tmc::hud::CraftingTableHud(100, 100, 
			inventory_slot_width*quick_use_slots + inventory_screen_pos_x + 100,
			inventory_screen_pos_y,
			inventory_slot_width,
			inventory_slot_height,
			inventory_slot_border);
    add_hud(inventory_hud);
    add_hud(full_inventory_hud);
	add_hud(static_cast<tgl::HudElement*>(crafting_table_hud));
    return;
    //add_hud();
#endif
}

extern tgl::Actor debug_actor;

void Player::tick(double time_delta)
{
    tgl::Player::tick(time_delta);
    static double time_since_last_left = 10;
    static double time_since_last_right = 10;
    static double time_since_last_e = 10;
    time_since_last_left += time_delta;
    time_since_last_right += time_delta;
    time_since_last_e += time_delta;
	glm::vec2 mouse_pos = glm::vec2(input_handler.mouse_x, input_handler.mouse_y);
	mouse_pos.y = tgl::global::window_height - mouse_pos.y;

	if (crafting_table_on)
	{
		crafting_table_hud->visible = true;
	}
	else
	{
		crafting_table_hud->visible = false;
	}
	if (input_handler.key_press[1] && hud_dragging == nullptr && 
		time_since_last_left >= multi_press_threshold)
	{
		tgl::HudElement * out_he = nullptr;
		screen_pos_to_inventory_index(mouse_pos.x, mouse_pos.y,
			dragged_inventory_index, out_he);
		if (dragged_inventory_index >= 0)
		{
			hud_dragging = new tmc::hud::InventorySlot(
				*dynamic_cast<tmc::hud::InventorySlot*>(out_he));
			if (dragged_inventory_index < quick_use_slots)
			{
				hud_dragging->pos += inventory_hud->pos;
			}
			else
			{
				hud_dragging->pos += full_inventory_hud->pos;
			}
			orig_drag_pos = hud_dragging->pos;
			drag_mouse_diff = mouse_pos;
			hud.push_back(hud_dragging);
		}
	}
	else if (input_handler.key_press[1] &&
		     time_since_last_left >= multi_press_threshold)
	{
		if (hud_dragging != nullptr)
		{
			tgl::HudElement * out_he = nullptr;
			int swap_item_index = -1;
			screen_pos_to_inventory_index(mouse_pos.x, mouse_pos.y,
				swap_item_index, out_he);
			if (swap_item_index != -1)
			{
				inventory.swap_items(swap_item_index, dragged_inventory_index);
			}
			delete hud_dragging;
			hud_dragging = nullptr;
			hud.resize(hud.size() - 1);
			hud_dragging = nullptr;
		}

	}
	if (hud_dragging != nullptr)
	{
		hud_dragging->pos += mouse_pos - drag_mouse_diff;
		drag_mouse_diff = mouse_pos;
	}
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
    if (input_handler.key_states['e'])
    {
        if (time_since_last_e >= multi_press_threshold)
        {
            inventory_on = !inventory_on;
            full_inventory_hud->visible = inventory_on;
            if (inventory_on)
            {
                enable_mouse_cursor(true);
            }
            else
            {
                enable_mouse_cursor(false);
            }
        }
        time_since_last_e = 0;
    }
#ifdef _TGL_CLIENT
    for (int i = 0; i < quick_use_slots; ++i)
    {
        if (input_handler.key_states['1' + i])
        {
            equipped_item = inventory.get_item(i);
            equipped_index = i;
        }
    }
    for (int i = 0; i < quick_use_slots; ++i)
    {
        if (i == equipped_index)
        {
            inventory_hud->sub_elements[i]->color = equipped_border_color;
            // hud[0]->sub_elements[2*i]->color = equipped_border_color;
        }
        else
        {
            inventory_hud->sub_elements[i]->color = unequipped_border_color;
        }
        tgl::InventoryItem * next_item = inventory.get_item(i);
        auto picture_element =
            static_cast<tmc::hud::InventorySlot*>(
                inventory_hud->sub_elements[i])->picture_element;
        auto text_element =
            static_cast<tmc::hud::InventorySlot*>(
                inventory_hud->sub_elements[i])->text_element;
        if (next_item != nullptr)
        {
            picture_element->set_offsets(
                tgl::useful_structures::
                    item_id_to_texture_coords[next_item->type],
                tgl::useful_structures::
                    item_id_to_texture_coords[next_item->type] +
                    glm::vec2(16, 16));
            text_element->set_text(std::to_string(next_item->quantity));
        }
        else
        {
            picture_element->set_offsets(
                glm::vec2(16, 8 * 16),
                glm::vec2(16, 8 * 16) + glm::vec2(16, 16));
            text_element->set_text("");
        }
    }
    for (int i = 0; i < inventory_slots - tgl::Inventory::default_quick_use_size; ++i)
    {
        full_inventory_hud->sub_elements[i]->color = unequipped_border_color;
        int inventory_index = i + tgl::Inventory::default_quick_use_size;
        tgl::InventoryItem * next_item = 
            inventory.get_item(inventory_index);
        auto picture_element = 
            static_cast<tmc::hud::InventorySlot*>(
                full_inventory_hud->sub_elements[i])->picture_element;
        auto text_element = 
            static_cast<tmc::hud::InventorySlot*>(
                full_inventory_hud->sub_elements[i])->text_element;
        if (next_item != nullptr)
        {
            picture_element->set_offsets(
                tgl::useful_structures::
                item_id_to_texture_coords[next_item->type],
                tgl::useful_structures::
                item_id_to_texture_coords[next_item->type] +
                glm::vec2(16, 16));
            text_element->set_text(
                std::to_string(next_item->quantity));
        }
        else
        {
            picture_element->set_offsets(
                glm::vec2(16, 8 * 16),
                glm::vec2(16, 8 * 16) + glm::vec2(16, 16));
            text_element->set_text("");
        }
    }
#else
    equipped_item = inventory.get_item(equipped_index);
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

int Player::screen_pos_to_inventory_index(int in_pos_x, int in_pos_y, 
	int &inventory_index, tgl::HudElement *& out_hud_element)
{
	int inventory_count = 0;
	for (auto he : inventory_hud->sub_elements)
	{
		if (in_pos_x < inventory_hud->pos.x + he->pos.x + he->width &&
			in_pos_y < inventory_hud->pos.y + he->pos.y + he->height &&
			in_pos_x > inventory_hud->pos.x + he->pos.x &&
			in_pos_y > inventory_hud->pos.y + he->pos.y)
		{
			if (dynamic_cast<tmc::hud::InventorySlot*>(he) != nullptr)
			{
				out_hud_element = he;
				inventory_index = inventory_count;
				return inventory_count;
			}
		}
		inventory_count += 1;
	}
	for (auto he : full_inventory_hud->sub_elements)
	{
		if (in_pos_x < full_inventory_hud->pos.x + he->pos.x + he->width &&
			in_pos_y < full_inventory_hud->pos.y + he->pos.y + he->height &&
			in_pos_x > full_inventory_hud->pos.x + he->pos.x &&
			in_pos_y > full_inventory_hud->pos.y + he->pos.y)
		{
			if (dynamic_cast<tmc::hud::InventorySlot*>(he) != nullptr)
			{
				out_hud_element = he;
				inventory_index = inventory_count;
				if (he == nullptr)
				{
					printf("TEST\n");
				}
				return inventory_count;
			}
		}
		inventory_count += 1;
	}
	inventory_index = -1;
	return -1;
}

}  // namespace tmc
