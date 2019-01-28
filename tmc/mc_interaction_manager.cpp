#include "tgl/globals.h"
#include "tmc/mc_interaction_manager.h"
#include "tmc/dropped_item.h"

namespace tmc
{

void InteractionManager::tick(double time_delta, std::vector<tgl::Actor*>& actors)
{
    for (auto actor : actors)
    {
        if (dynamic_cast<tmc::ChunkSpawn*>(actor) != nullptr)
        {
            chunk_spawn = dynamic_cast<tmc::ChunkSpawn*>(actor);
        }
    }
    for (auto actor : actors)
    {
        if (dynamic_cast<tmc::Player*>(actor) != nullptr)
        {
            // Process block hits
            tmc::Player * player = static_cast<tmc::Player*>(actor);
            std::vector<glm::vec3> hits = player->fetch_hits();
            for (auto hit : hits)
            {
                glm::vec3 eye_loc = player->get_eye_loc();
                e_block_type hit_type;
                glm::vec3 block_to_add;
                glm::vec3 intersect_point;
                std::cout << "POSTED HIT " << eye_loc.y << "\n";
                glm::vec3 hit_block =
                    chunk_spawn->get_block_pointed_at(eye_loc,
                                                      hit,
                                                      player->max_hit_distance,
                                                      hit_type,
                                                      block_to_add,
                                                      intersect_point);
                if (chunk_spawn != nullptr)
                {
                    tgl::InventoryItem& check = player->get_equipped();
                    if (check.type != tgl::ItemId::none)
                    {
                        tmc::BlockHit hit_to_post;
                        hit_to_post.loc = hit_block;
                        if (tgl::global::server_processing)
                        {
                            chunk_spawn->post_hit(hit_to_post);
                        }
                        // std::cout << "POSTED HIT" << "\n";
                    }
                }
            }
            
            // Process block placements
            std::vector<std::pair<glm::vec3, e_block_type>> placements = 
                player->fetch_placements();
            for (auto placement : placements)
            {
                glm::vec3 eye_loc = player->get_eye_loc();
                e_block_type hit_type;
                glm::vec3 block_to_add_loc;
                glm::vec3 intersect_point;
                std::cout << "POSTED HIT " << eye_loc.y << "\n";
                glm::vec3 hit_block =
                    chunk_spawn->get_block_pointed_at(eye_loc,
                                                      placement.first,
                                                      player->max_hit_distance,
                                                      hit_type,
                                                      block_to_add_loc,
                                                      intersect_point);
                if (chunk_spawn != nullptr)
                {
					BlockState * block_state = nullptr;
					block_state = chunk_spawn->get_block_state(hit_block);
					if (block_state != nullptr)
					{

					}
					else
					{
						tgl::InventoryItem& check = player->get_equipped();
						if (check.type != tgl::ItemId::none)
						{
							block_def block_to_place;
							block_to_place.loc = block_coord(block_to_add_loc);
							block_to_place.type =
								item_id_to_block_type(check.type);
							if (tgl::global::server_processing)
							{
								chunk_spawn->post_placement(block_to_place);
							}
						}
					}
                }
            }
            
            // Collect dropped items
            std::vector <tgl::Actor*> collected_items =
                chunk_spawn->collect_nearby_dropped_items(player->get_pos(),
                                                player->item_collect_radius);
            for (auto item : collected_items)
            {
                player->inventory.change_quantity(((tmc::DroppedItem*)item)->item_type, 1);
                item->flag_for_deletion(true);
            }
        }
    }
}

}  // namespace tmc