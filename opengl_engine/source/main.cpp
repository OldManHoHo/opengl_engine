
#include "tgl_gl.h"

#include <iostream>

#include "TGLBase.h"
#include "TGLCamera.h"
#include "TMCPlayer.h"
#include "TGLChunkSpawn.h"
#include "useful_structures.h"

#ifdef _UNIT_TEST
#include "Simplex.h"
#endif

//extern std::vector <GLfloat> useful_structures::vertex_data_block_small;

TGLBase gl_base;
TGLActor debug_actor;
class rot_actor : public TGLActor
{
	void tick(double time_delta)
	{
		static_physics = true;
		static float d_rot = 0;
		d_rot += 0.01;
		glm::mat4 out_transform(1.0);
		out_transform = glm::translate(out_transform, glm::vec3(0, 195, 0));
		out_transform = glm::rotate(out_transform, d_rot, glm::vec3(0, 0, 1));
		out_transform = glm::rotate(out_transform, d_rot, glm::vec3(0, 1, 0));
		
		
		set_transform(out_transform);
	}
};

int main()
{
#ifdef _UNIT_TEST
	Simplex_TEST();
#endif
	
	gl_base.init();

#ifdef _TGL_CLIENT
	TGLHudElement inventory(600, 120, glm::vec2(100,100), glm::vec3(0.2, 0.2, 0.2));
	int offset = 10;
	int shift = 120;
	TGLHudElement inventory_item(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/pickaxe.png");
	TGLHudElement inventory_itemb(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	TGLHudElement inventory_item2(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png", 0, 0, 16, 16);
	TGLHudElement inventory_item2b(120, 120, glm::vec2(offset-10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	TGLHudElement inventory_item3(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png");
	TGLHudElement inventory_item3b(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	TGLHudElement inventory_item4(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png");
	TGLHudElement inventory_item4b(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	TGLHudElement inventory_item5(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png");
	TGLHudElement inventory_item5b(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	inventory.sub_elements.push_back(&inventory_itemb);
	inventory.sub_elements.push_back(&inventory_item);
	inventory.sub_elements.push_back(&inventory_item2b);
	inventory.sub_elements.push_back(&inventory_item2);
	inventory.sub_elements.push_back(&inventory_item3b);
	inventory.sub_elements.push_back(&inventory_item3);
	inventory.sub_elements.push_back(&inventory_item4b);
	inventory.sub_elements.push_back(&inventory_item4);
	inventory.sub_elements.push_back(&inventory_item5b);
	inventory.sub_elements.push_back(&inventory_item5);


	TGLHudElement depth_buffer_display(500, 500, glm::vec2(100, 500), glm::vec3(0, 0, 0), "content/textures/mc.png");
	depth_buffer_display.tex->texture = gl_base.ray_bounce.depthTexture;

	TGLHudElement depth_buffer_display2(500, 500, glm::vec2(100, 1050), glm::vec3(0, 0, 0), "content/textures/mc.png");
	depth_buffer_display2.tex->texture = gl_base.ray_bounce.depthTexture2;

	debug_actor.add_component(useful_structures::create_cube_mesh());
#endif
	debug_actor.set_scale(glm::vec3(0.1,0.1,0.1));

	TGLChunkSpawn chunk_spawn;
	gl_base.set_world_actor((TGLActor*)&chunk_spawn);

	//TGLPlayer main_cam;
	TMCPlayer main_cam;
	// TMCPlayer p1;
	// TMCPlayer p2;
	// TMCPlayer p3;
	// TMCPlayer p4;
	// TMCPlayer p5;
	// TMCPlayer p6;
	
	main_cam.set_chunk_spawn(&chunk_spawn);
	
	
	//gl_base.add_actor(&main_cam);
	// gl_base.add_actor(&p1);
	// gl_base.add_actor(&p2);
	// gl_base.add_actor(&p3);
	// gl_base.add_actor(&p4);
	// gl_base.add_actor(&p5);
	// gl_base.add_actor(&p6);
	gl_base.add_actor(&chunk_spawn);
	gl_base.add_actor(&debug_actor);
#ifdef _TGL_CLIENT
	gl_base.add_camera(&main_cam);
	main_cam.add_hud(&inventory);
	gl_base.add_hud_element(&inventory);
	gl_base.add_hud_element(&depth_buffer_display);
	gl_base.add_hud_element(&depth_buffer_display2);
#endif
	//debug_actor.set_pos(glm::vec3(0, 185, 0));
	gl_base.start_tasks();
	while (1)
	{
		gl_base.update();
	}

	return 0;
}
