
#include "tgl/tgl_gl.h"

#include <iostream>
#ifdef _UNIT_TEST
#include <gtest/gtest.h>
#endif  // _UNIT_TEST

#include "tgl/base.h"
#include "tgl/camera.h"
#include "tgl/globals.h"
#include "tgl/useful_structures.h"
#include "tmc/mc_player.h"
#include "tmc/chunk_spawn.h"
#include "tmc/mc_interaction_manager.h"

tgl::Base gl_base; // TODO: Either make tgl::Base object accessible to classes
				 //
tgl::Actor debug_actor;


class rot_actor : public tgl::Actor
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

int main(int ac, char* av[])
{
#ifdef _UNIT_TEST
	testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
#endif
	gl_base.init();
	std::shared_ptr<tgl::Base> test_ptr(&gl_base);
#ifdef _TGL_CLIENT
	tgl::HudElement inventory(600, 120, glm::vec2(100,100), glm::vec3(0.2, 0.2, 0.2));
	int offset = 10;
	int shift = 120;
	tgl::HudElement inventory_item(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/pickaxe.png");
	tgl::HudElement inventory_itemb(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	tgl::HudElement inventory_item2(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png", 0, 0, 16, 16);
	tgl::HudElement inventory_item2b(120, 120, glm::vec2(offset-10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	tgl::HudElement inventory_item3(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png");
	tgl::HudElement inventory_item3b(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	tgl::HudElement inventory_item4(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png");
	tgl::HudElement inventory_item4b(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
	offset += shift;
	tgl::HudElement inventory_item5(100, 100, glm::vec2(offset, 10), glm::vec3(0.5, 0.5, 0.5), "content/textures/mc.png");
	tgl::HudElement inventory_item5b(120, 120, glm::vec2(offset - 10, 0), glm::vec3(0.5, 0.5, 0.5));
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

	debug_actor.add_component(tgl::useful_structures::create_cube_mesh());
#endif
	debug_actor.set_scale(glm::vec3(0.1,0.1,0.1));

	std::shared_ptr<tmc::ChunkSpawn> chunk_spawn = gl_base.add_actor<tmc::ChunkSpawn>();
	gl_base.set_world_actor((tgl::Actor*)(chunk_spawn.get()));

	//tgl::Player main_cam;
	std::shared_ptr<tmc::Player> main_cam = gl_base.add_actor<tmc::Player>();
	// TMCPlayer p1;
	// TMCPlayer p2;
	// TMCPlayer p3;
	// TMCPlayer p4;
	// TMCPlayer p5;
	// TMCPlayer p6;
	
	main_cam->set_chunk_spawn(chunk_spawn.get());


#ifdef _TGL_CLIENT
    tgl::HudElement * depth_buffer_display = new tgl::HudElement(500, 500, glm::vec2(100, 500), glm::vec3(0, 0, 0), "content/textures/mc.png");
    depth_buffer_display->tex->texture = gl_base.ray_bounce.depthTexture;
    main_cam->add_hud(depth_buffer_display);

    tgl::HudElement * depth_buffer_display2 = new tgl::HudElement(500, 500, glm::vec2(100, 1050), glm::vec3(0, 0, 0), "content/textures/mc.png");
    depth_buffer_display2->tex->texture = gl_base.ray_bounce.depthTexture2;
    main_cam->add_hud(depth_buffer_display2);
    if (tgl::global::server_processing)
    {
        //gl_base.add_actor(&main_cam);
    }
    tgl::HudElement * the;
    tgl::HudElement * the2;
    
    //the = new tgl::HudElement(
    //    375,
    //    75,
    //    glm::vec2(1000, 1000),
    //    glm::vec3(0, 0, 0),
    //    std::string("TEst TextTTT"),
    //    0,
    //    0,
    //    0,
    //    0);
    //main_cam.add_hud(the);
#endif
	// gl_base.add_actor(&p1);
	// gl_base.add_actor(&p2);
	// gl_base.add_actor(&p3);
	// gl_base.add_actor(&p4);
	// gl_base.add_actor(&p5);
	// gl_base.add_actor(&p6);
	//gl_base.add_actor(&chunk_spawn);
	//gl_base.add_actor(&debug_actor);
#ifdef _TGL_CLIENT
    if (tgl::global::server_processing)
    {
        gl_base.add_camera(main_cam.get());
    }
	//main_cam.add_hud(&inventory);
	//gl_base.add_hud_element(&inventory);
	//gl_base.add_hud_element(&depth_buffer_display);
	//gl_base.add_hud_element(&depth_buffer_display2);
#endif
	//debug_actor.set_pos(glm::vec3(0, 185, 0));
	gl_base.start_tasks();
	while (1)
	{
		gl_base.update();
	}

	return 0;
}
