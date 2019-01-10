
#include "tgl/actor.h"
#include "tgl/material.h"
#include "tgl/mesh.h"
#include "tgl/mesh_vertices.h"
#include "tgl/useful_structures.h"

namespace tmc
{

class DroppedItem :
	public tgl::Actor
{
public:
	tgl::ItemId item_type;

	DroppedItem(tgl::ItemId in_item_type);
	~DroppedItem();
};

} // namespace tmc