#include "tmc/hud/crafting_table_hud.h"

namespace tmc
{
namespace hud
{

CraftingTableHud::CraftingTableHud(int size_x, int size_y, int pos_x, int pos_y,
	int in_inventory_slot_width,
	int in_inventory_slot_height,
	int in_inventory_slot_border):
		inventory_slot_height(in_inventory_slot_height),
		inventory_slot_width(in_inventory_slot_width),
		inventory_slot_border(in_inventory_slot_border),
		tgl::HudElement(size_x,
			size_y,
			glm::vec2(pos_x, pos_y),
			glm::vec3(0.0, 0.0, 0.0))
{
	tmc::hud::InventorySlotGroup * temp_group = new tmc::hud::InventorySlotGroup(0, 0,
		16, 4,
		inventory_slot_width,
		inventory_slot_height,
		inventory_slot_border);
	sub_elements.push_back(static_cast<tgl::HudElement*>(temp_group));
}

}  // namespace hud
}  // namespace tmc
