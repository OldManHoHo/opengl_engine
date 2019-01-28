#ifndef TMC_HUD_CRAFTING_TABLE_HUD_H_
#define TMC_HUD_CRAFTING_TABLE_HUD_H_

#include "tgl/hud_element.h"
#include "tmc/hud/inventory_slot_group.h"

namespace tmc
{
namespace hud
{
    
class CraftingTableHud : public tgl::HudElement
{
    int size_x;
    int size_y;
	int inventory_slot_width;
	int inventory_slot_height;
	int inventory_slot_border;
    
 public:
    CraftingTableHud(int size_x, int size_y, int pos_x, int pos_y,
		int in_inventory_slot_width,
		int in_inventory_slot_height,
		int in_inventory_slot_border);
};
    
}  // namespace hud   
}  // namespace tmc

#endif  // TMC_HUD_CRAFTING_TABLE_HUD_H_