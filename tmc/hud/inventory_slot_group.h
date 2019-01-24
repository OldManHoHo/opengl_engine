#ifndef TMC_HUD_INVENTORY_SLOT_GROUP_H_
#define TMC_HUD_INVENTORY_SLOT_GROUP_H_

#include "tgl/hud_element.h"

namespace tmc
{
namespace hud
{
    
class InventorySlotGroup : public tgl::HudElement
{
    // Number of total items
    int num_items;
    // Number of items in each row
    int num_columns;
    
    // Graphical specifications
    int inventory_slot_border;
    int inventory_slot_height;
    int inventory_slot_width;
    
    InventorySlotGroup(int in_pos_x, int in_pos_y,
                  int in_num_items, int in_num_columns,
                  int in_inventory_slot_width,
                  int in_inventory_slot_height,
                  int in_inventory_slot_border);
};
    
}  // namespace hud
}  // namespace tmc