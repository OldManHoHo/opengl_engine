#ifndef TMC_DROPPED_ITEM_H_
#define TMC_DROPPED_ITEM_H_

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

    explicit DroppedItem(tgl::ItemId in_item_type);
    ~DroppedItem();
};

}  // namespace tmc

#endif  // TMC_DROPPED_ITEM_H_
