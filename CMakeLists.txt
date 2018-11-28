cmake_minimum_required (VERSION 3.6)
project (TGL_Server)

file (GLOB SRC ./main.cpp 
		./TGLBase.cpp)

add_executable(tgl_server ${SRC})

