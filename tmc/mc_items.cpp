#include "mc_items.h"

namespace tgl
{
    
int block_place_range = static_cast<int>(iid_sand_block) + 1;

e_block_type item_id_to_block_type(ItemId item_id)
{
    if (item_id < block_place_range && item_id != none)
    {
        return static_cast<e_block_type>(item_id);
    }
    return bt_invalid;
}

ItemId block_type_to_item_id(e_block_type in_block_type)
{
    return static_cast<ItemId>(in_block_type);
    return none;
}

}  // namespace tgl