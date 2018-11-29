cmake_minimum_required (VERSION 2.8)
project (TGL_Server)


set (top "./opengl_engine")
set (tmc "./tmc")
include_directories(${top}/)
include_directories(${top}/include)
include_directories(${top}/glm-0.9.9-a2)
include_directories(${tmc})
include_directories(${top}/FastNoiseSIMD)

set (SRC ${top}/source/main.cpp
	${top}/TGLBase.cpp
	${top}/TGLActor.cpp
	${top}/useful_structures.cpp
	${top}/TGLChunkSpawn.cpp
	${tmc}/TMCPlayer.cpp
	${top}/TGLPlayer.cpp
	${top}/TGLPhysicsEngine.cpp
	${top}/BlockGenerator.cpp
	${top}/TGLInventory.cpp
	${top}/TGLCamera.cpp
	${top}/TGLInputHandler.cpp
	${top}/TGLComponent.cpp
	${top}/TMCDroppedItem.cpp
	${top}/Simplex.cpp
	${top}/WhiteNoise.cpp
	${top}/FastNoiseSIMD/FastNoiseSIMD.cpp
	${top}/FastNoiseSIMD/FastNoiseSIMD_internal.cpp
	${top}/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp
	${top}/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp
	${top}/Generator.cpp
	)

#	${top}/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp
#	${top}/FastNoiseSIMD/FastNoiseSIMD_avx512.cpp
#	${top}/FastNoiseSIMD/FastNoiseSIMD_neon.cpp
add_compile_options(-std=c++11)
add_compile_options(-D_EXCLUDE_TMC_DROPPED_ITEM)

add_executable(tgl_server ${SRC})

