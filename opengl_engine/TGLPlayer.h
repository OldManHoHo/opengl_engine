#pragma once
#ifndef _TGL_PLAYER
#define _TGL_PLAYER


#include <vector>

#include "TGLCamera.h"
#include "TGLMesh.h"
#include "TGLInventory.h"
#include "TGLHudElement.h"


class TGLPlayer : public TGLCamera
{
	TGLMesh * debug_block;
	std::vector <TGLHudElement*> hud;
	TGLInventoryItem * equipped_item;
	TGLInventory inventory;

public:
	float y_angle;
	float x_angle;

	glm::vec3 crosshair;

	bool hitting_bool;
	glm::vec3 hitting;

	TGLPlayer();
	~TGLPlayer();
	void tick(double time_delta);
	void set_hitting(glm::vec3 in_hitting);
	glm::vec3 get_hitting();
	void add_hud(TGLHudElement * in_hud);
	TGLInventoryItem& get_equipped();
	bool change_inventory_amount(TGLItemId item_type, int in_amount);
};

#endif