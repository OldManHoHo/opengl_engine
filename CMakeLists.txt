cmake_minimum_required (VERSION 2.8)
project (TGL_Server)


set (top "./")
set (tgl "./tgl")
set (tmc "./tmc")
set (fnsd "./FastNoiseSIMD")
include_directories(${top}/)
include_directories(${top}/include)
include_directories(${top}/glm-0.9.9-a2)
#include_directories(${tmc})
include_directories(${top}/FastNoiseSIMD)

set (SRC ${tmc}/main.cpp
	${tgl}/base.cpp
	${tgl}/actor.cpp
	${tgl}/useful_structures.cpp
	${tmc}/chunk_spawn.cpp
	${tmc}/mc_player.cpp
	${tmc}/chunk_database.cpp
	${tgl}/player.cpp
	${tgl}/physics_engine.cpp
	${tmc}/block_generator.cpp
	${tgl}/inventory.cpp
	${tgl}/camera.cpp
	${tgl}/input_handler.cpp
	${tgl}/component.cpp
    ${tgl}/udp_interface.cpp
	${tmc}/dropped_item.cpp
	${tgl}/library_queue.cpp
	${tgl}/game_state.cpp
	${tmc}/simplex.cpp
	${tmc}/white_noise.cpp
	${fnsd}/FastNoiseSIMD.cpp
	${fnsd}/FastNoiseSIMD_internal.cpp
	${fnsd}/FastNoiseSIMD_sse2.cpp
	${fnsd}/FastNoiseSIMD_sse41.cpp
	${tmc}/generator.cpp
	${tmc}/mc_items.cpp
	${tmc}/mc_interaction_manager.cpp
	)

#	${tgl}/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp
#	${tgl}/FastNoiseSIMD/FastNoiseSIMD_avx512.cpp
#	${tgl}/FastNoiseSIMD/FastNoiseSIMD_neon.cpp
add_compile_options(-std=c++11 -ggdb)
add_compile_options(-D_TGL_SERVER)
add_compile_options(-DGLM_ENABLE_EXPERIMENTAL)
#add_compile_options(-D_UNIT_TEST)
#add_compile_options(-D_EXCLUDE_TMC_DROPPED_ITEM)


add_executable(tgl_server ${SRC})


find_library(libprotobuf protobuf)
target_link_libraries(tgl_server ${libprotobuf})
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(tgl_server PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(tgl_server "${CMAKE_THREAD_LIBS_INIT}")
endif()
