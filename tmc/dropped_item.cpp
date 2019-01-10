#include "tmc/dropped_item.h"

namespace tmc
{

DroppedItem::DroppedItem(tgl::ItemId in_item_type):
	item_type(in_item_type)
{

	tgl::Bounds * new_bounds = new tgl::BlockBounds(0.3, 0.3, 0.3);
	set_bounds(new_bounds);
	mass = 10;
	{
#ifdef _TGL_CLIENT
		add_component(useful_structures::create_cube_mesh());
#endif
		set_scale(glm::vec3(0.1, 0.1, 0.1));
	}
}


DroppedItem::~DroppedItem()
{
}

} // namespace tmc