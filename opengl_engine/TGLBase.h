#pragma once
#ifndef _TGL_BASE
#define _TGL_BASE

#define GLM_ENABLE_EXPERIMENTAL

#include "tgl_gl.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>

#include "TGLMesh.h"
#include "TGLCamera.h"
#include "TGLPlayer.h"
#include "TGLPhysicsEngine.h"
#include "TGLHudElement.h"
#include "TGLUDPInterface.h"
#include "TGLGameState.h"
#include "TGL_USER_CLASSES.h"

#ifdef _TGL_CLIENT
#include "TGLRayBounce.h"
#endif

#ifndef _TGL_CLIENT
class TGLClientStatus
{
public:
	int actor_id;
	std::chrono::steady_clock::time_point time_of_last_heartbeat;
};
#endif

class TGLBase
{
	int window_height;
	int window_width;
	
	TGLUDPInterface udp_interface;
	std::vector <char> game_state_buf;
#ifdef _TGL_CLIENT
	GLFWwindow* window;
#else
    std::map <udp_address, TGLClientStatus> clients;
    double heartbeat_period;
    double tick_rate;
    std::chrono::steady_clock::time_point time_of_last_send;
#endif

	std::vector <TGLMesh*> meshes;
	std::vector <TGLActor*> actors;
	std::vector <TGLHudElement*> HUD_elements;
	TGLCamera * active_camera;
	TGLActor * chunks_spawner;
	TGLPhysicsEngine physics_engine;

	std::chrono::steady_clock::time_point end;
	std::chrono::steady_clock::time_point begin;
	double time_sum;
	int time_count;

	GLuint default_shader_program;

	glm::vec3 shadow_pos1;
	glm::vec3 shadow_pos2;
	glm::mat4 depthMVP1;
	glm::mat4 depthMVP2;
	glm::vec3 sun_pos_buf1;
	glm::vec3 sun_pos_buf2;

	bool shadow_maps_enabled;
	glm::vec3 sun_pos;
	glm::vec3 sun_intensity;
	glm::vec3 sun_dir;

public:

	TGLBase();
	~TGLBase();

#ifdef _TGL_CLIENT
	TGLRayBounce ray_bounce;
	bool gl_init();
	GLFWwindow * gl_create_window(int in_width, int in_height);
	bool glad_init();
	void processInput(GLFWwindow *window);
	GLFWwindow * get_window();
	void add_camera(TGLCamera * in_camera);
	void add_hud_element(TGLHudElement * in_element);
	void apply_game_state(std::vector <char> * in_state);
	void process_msg(std::pair<sockaddr_in, std::vector<char>>* in_pair);
#else
    void generate_game_state(bool full);
    void send_game_state_to_all();
    void update_clients();
    void process_msg(std::pair<sockaddr_in, std::vector<char>>* in_pair);
#endif

	
	int init();
	void update();
	void add_mesh(TGLMesh * in_mesh);
	void add_actor(TGLActor * in_actor);
	void remove_actor(TGLActor * in_actor);
	
	TGLPlayer * get_player();
	glm::vec3 get_player_pos();
	void set_world_actor(TGLActor * in_actor);
	void get_game_state();
	void update_sun(double time_delta);
	
	void recalculate_light(int in_chunk_x, int in_chunk_y);
};


#endif
