#include "TMCPlayer.h"

TMCPlayer::TMCPlayer():
    chunk_spawn(nullptr),
    equipped_border_color(0.4,0.4,0.4),
    unequipped_border_color(0.2,0.2,0.2)
{
    init_inventory(inventory.default_quick_use_size);
}

void TMCPlayer::init_inventory(int num_slots)
{
    TGLHudElement inventory(inventory_slot_width*num_slots, inventory_slot_height, glm::vec2(inventory_screen_pos_x, inventory_screen_pos_y), glm::vec3(0.0, 0.0, 0.0));
	int offset = inventory_slot_border;
	int shift = inventory_slot_width;
	for (int i = 0; i < num_slots; ++i)
	{
	    TGLHudElement * inventory_itemb = new TGLHudElement(inventory_slot_width, inventory_slot_height, glm::vec2(i*inventory_slot_width, 0), glm::vec3(0.5, 0.5, 0.5));
	    TGLHudElement * inventory_item = new TGLHudElement(inventory_slot_width - 2*inventory_slot_border, 
	                                inventory_slot_height - 2*inventory_slot_border, 
	                                glm::vec2(i*inventory_slot_width + inventory_slot_border, 
	                                inventory_slot_border), glm::vec3(0.5, 0.5, 0.5), 
	                                "content/textures/pickaxe.png");
	    inventory.sub_elements.push_back(inventory_itemb);
	    inventory.sub_elements.push_back(inventory_item);
	}
}

void TMCPlayer::tick(double time_delta)
{
    TGLPlayer::tick(time_delta);
    
    if (glfwGetMouseButton(gl_base.get_window(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		glm::vec3 forward_vector(1.0, 0.0, 0.0);
		
		forward_vector = glm::mat3(get_rot())*forward_vector;
		//forward_vector += pos;
		//forward_vector += glm::vec3(0.0, 0.5, 0);
		
		set_hitting(forward_vector);
		e_block_type hit_type;
		glm::vec3 block_to_add;
		glm::vec3 hit_block = get_block_pointed_at(get_pos(), forward_vector, max_hit_distance, hit_type, block_to_add);
		
		
		if (chunk_spawn != nullptr)
		{
		    hit_properties props = get_equipped().get_hit_properties();
		    block_hit hit_to_post;
		    hit_to_post.loc = hit_block;
		    hit_to_post.props = props;
		    chunk_spawn->post_hit(block_hit);
		}
	}
	if (glfwGetMouseButton(gl_base.get_window(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		glm::vec3 forward_vector(1.0, 0.0, 0.0);
		
		forward_vector = glm::mat3(get_rot())*forward_vector;
		//forward_vector += pos;
		//forward_vector += glm::vec3(0.0, 0.5, 0);
		
		set_hitting(forward_vector);
		e_block_type hit_type;
		glm::vec3 block_to_add;
		glm::vec3 hit_block = get_block_pointed_at(get_pos(), forward_vector, max_hit_distance, hit_type, block_to_add);
		
		
		if (chunk_spawn != nullptr)
		{
		    e_block_type type_to_add = item_id_to_block_type(get_equipped().type);
		    chunk_spawn->post_placement(block_to_add, type_to_add);
		    change_inventory_amount(get_equipped().type, -1);
		}
	}
	
	int equipped_index = 0;
	for (i = 0; i < inventory.default_quick_use_size; ++i)
	{
	    if (glfwGetKey(gl_base.get_window(), GLFW_KEY_1 + i) == GLFW_PRESS)
    	{
    		equipped_item = inventory.get_item(i, 0);
    		equipped_index = i;
    	}
	}
	for (i = 0; i < inventory.default_quick_use_size; ++i)
	{
	    if (i == equipped_index)
	    {
	        hud[0]->sub_elements[2*i]->color = equipped_border_color;
	    }
	    else
	    {
	        hud[0]->sub_elements[2*i]->color = unequipped_border_color;
	    }
	    
	    TGLInventoryItem * next_item = inventory.get_item(i, 0);
	    int index = i*2 + 1;
    	if (next_item != nullptr)
    	{
    		hud[0]->sub_elements[index]->set_offsets(useful_structures::item_id_to_texture_coords[next_item->type], useful_structures::item_id_to_texture_coords[next_item->type] + glm::vec2(16, 16));
    	}
    	else
    	{
    		hud[0]->sub_elements[index]->set_offsets(glm::vec2(16, 8 * 16), glm::vec2(16, 8 * 16) + glm::vec2(16, 16));
    	}
	}
}

void TMCPlayer::set_chunk_spawn(TGLChunkSpawn * in_chunk_spawn)
{
    chunk_spawn = in_chunk_spawn;
}

void TMCPlayer::add_quick_slot()
{
    
}