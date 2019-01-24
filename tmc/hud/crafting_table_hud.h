#ifndef TMC_HUD_CRAFTING_TABLE_HUD_H_
#define TMC_HUD_CRAFTING_TABLE_HUD_H_

#include "tgl/hud_element.h"
#include "tmc/hud/inventory_slot_group.h"

namespace tmc
{
namespace hud
{
    
class CraftingTableHud : tgl::HudElement
{
    int size_x;
    int size_y;
    
 public:
    CraftingTableHud(int size_x, int size_y, int pos_x, int pos_y);
};
    
}  // namespace hud   
}  // namespace tmc

#endif  // TMC_HUD_CRAFTING_TABLE_HUD_H_