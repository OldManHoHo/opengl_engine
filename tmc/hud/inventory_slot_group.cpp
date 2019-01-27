#include "tmc/hud/inventory_slot_group.h"

namespace tmc
{
namespace hud
{
    
InventorySlotGroup::InventorySlotGroup(int in_pos_x, int in_pos_y,
                      int in_num_items, int in_num_columns,
                      int in_inventory_slot_width,
                      int in_inventory_slot_height,
                      int in_inventory_slot_border):
    num_items(in_num_items),
    num_columns(in_num_columns),
    inventory_slot_height(in_inventory_slot_height),
    inventory_slot_width(in_inventory_slot_width),
    inventory_slot_border(in_inventory_slot_border),
    tgl::HudElement(in_num_columns*inventory_slot_width,
            ceil(in_num_items*1.0/in_num_columns)*inventory_slot_height,
            glm::vec2(in_pos_x, in_pos_y),
            glm::vec3(0.0, 0.0, 0.0))
{
    for (int i = 0; i < num_items; ++i)
    {
        int row_index = i % num_columns;
        int col_index = floor(i*1.0/num_columns);
        InventorySlot * new_slot = 
            new InventorySlot(
                     row_index*inventory_slot_width,
                     col_index*inventory_slot_height,
                     inventory_slot_width,
                     inventory_slot_height,
                     inventory_slot_border);
        sub_elements.push_back(new_slot);
    }
}
    
}  // namespace hud
}  // namespace tmc