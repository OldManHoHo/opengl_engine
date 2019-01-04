#pragma once
#ifndef _TGL_PLAYER
#define _TGL_PLAYER


#include <vector>

#include "TGLCamera.h"
#include "TGLMesh.h"
#include "TGLInventory.h"
#include "TGLHudElement.h"
#include "TGLInputHandler.h"

class TGLPlayer : public TGLCamera
{
	TGLMesh * debug_block;
	TGLInventoryItem blank_item;
	
protected:
	TGLInputHandler input_handler;

public:
	glm::vec3 forward_vec;
	double multi_press_threshold;
	std::vector <TGLHudElement*> hud;

	TGLInventory inventory;
	TGLInventoryItem * equipped_item;
	TGLHudElement * inventory_hud;

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
	void generate_input_msg(std::vector <char> & input_msg);
	void apply_input_msg(std::vector <char> & input_msg);
};

#endif