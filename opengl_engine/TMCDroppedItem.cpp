#include "TMCDroppedItem.h"

TMCDroppedItem::TMCDroppedItem(TGLItemId in_item_type):
	item_type(in_item_type)
{

	TGLBounds * new_bounds = new TGLBlockBounds(0.3, 0.3, 0.3);
	set_bounds(new_bounds);
	mass = 10;
	{
		add_component(useful_structures::create_cube_mesh());
		set_scale(glm::vec3(0.1, 0.1, 0.1));
	}
}


TMCDroppedItem::~TMCDroppedItem()
{
}
