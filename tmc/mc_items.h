#ifndef TMC_MC_ITEMS_H_
#define TMC_MC_ITEMS_H_

#include "tmc/block_generator.h"

namespace tgl
{

enum ItemId
{
    none,
    iid_dirt_with_grass_block,
    iid_dirt_block,
    iid_stone_block,
    iid_tree_block,
    iid_leaves_block,
    iid_water_block,
    iid_sand_block,
    pickaxe
};

e_block_type item_id_to_block_type(ItemId item_id);
ItemId block_type_to_item_id(e_block_type in_block_type);

class Item
{
    float efficiency;
    float durability;
    float weight;
    float comfort;
    ItemId type;
};

}  // namespace tgl

#endif  // TMC_MC_ITEMS_H_