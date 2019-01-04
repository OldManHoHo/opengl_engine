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

enum TGLObjectType
{
	world_object,
	player_object
};

class TGLBase
{
	std::map <std::string,float*> conf_float_values;
	std::map <std::string,double*> conf_double_values;
	std::map <std::string,std::string*> conf_string_values;
	std::map <std::string,int*> conf_int_values;
	std::map <std::string,bool*> conf_bool_values;
	
	int window_height;
	int window_width;
	
	TGLUDPInterface udp_interface;
	int client_udp_receive_port;
	int client_udp_send_port;
	int server_udp_receive_port;
	int server_udp_send_port;
	std::string server_ip_address;
	std::string client_ip_address;
	
	bool debug_console_enabled;
	std::mutex console_mutex;
	std::mutex console_queue_mutex;
	std::deque <std::string> console_queue;
	
	std::vector <char> game_state_buf;
	std::vector <char> player_input_buf;
#ifdef _TGL_CLIENT
	GLFWwindow* window;
#else
    std::map <udp_address, TGLClientStatus> clients;
#endif
    double heartbeat_period;
    double tick_rate;
    double client_input_update_rate;
    std::chrono::steady_clock::time_point time_of_last_send;
    std::chrono::steady_clock::time_point time_of_last_input_send;


	std::vector <TGLMesh*> meshes;
	std::vector <TGLActor*> actors;
	std::vector <TGLHudElement*> HUD_elements;
	TGLPlayer * active_camera;
	float player_fov;
	float player_start_pos_x;
	float player_start_pos_y;
	float player_speed;
	TGLActor * chunks_spawner;
	float chunk_spawn_tick_interval;
	float chunk_despawn_distance;
	int max_loaded_chunks;
	TGLPhysicsEngine physics_engine;
	bool gravity_enabled;
	float water_speed_multiplier;

	std::chrono::steady_clock::time_point end;
	std::chrono::steady_clock::time_point begin;
	
	float constant_time_delta;
	bool max_framerate_enabled;
	float max_framerate;
	
	//////////////////////////////
	// Interval counters
	
	// Counters used for shadow map update
	double shadow_map_counter;
	double shadow_map_interval;
	
	// CPU lighting counters
	double cpu_lighting_counter;
	double cpu_lighting_interval;
	bool cpu_lighting_enabled;
	
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
	float shadow_map_box_start_distance;
	float shadow_map_box_end_distance;
	float shadow_map_box_height;
	float shadow_map_box_width;
	
	bool day_night_cycle_enabled;
	float start_time_of_day;
	float time_of_day_multiplier;
	float cpu_light_ray_grid_division;
	float cpu_light_ray_grid_width;
	float cpu_light_second_bounce_radius;
	float cpu_light_first_hit_distance;
	int cpu_light_num_secondary_bounces;
	float cpu_light_bounce_multiplier;
	
	glm::vec3 sun_pos;
	glm::vec3 sun_intensity;
	glm::vec3 sun_dir;
	
	std::map <chunk_coord, std::map<block_coord, char>> light_calcs;

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
	void send_input_update();
#else
    void generate_game_state(bool full);
    void send_game_state_to_all();
    void update_clients();
    void process_msg(std::pair<sockaddr_in, std::vector<char>>* in_pair);
#endif

	
	int init();
	bool set_conf_value(std::string conf_var_name, std::string conf_var_value, bool only_print = false);
	void read_conf();
	void debug_console_loop();
	void start_tasks();
	void update();
	void add_mesh(TGLMesh * in_mesh);
	void add_actor(TGLActor * in_actor);
	void remove_actor(TGLActor * in_actor);
	
	TGLPlayer * get_player();
	glm::vec3 get_player_pos();
	void set_world_actor(TGLActor * in_actor);
	void get_game_state();
	void update_sun(double time_delta);

};


#endif
