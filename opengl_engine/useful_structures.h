#pragma once
#ifndef TGL_USEFUL_STRUCTURES_H_
#define TGL_USEFUL_STRUCTURES_H_

#ifdef _TGL_CLIENT
#include <windows.h>
#endif
#include <map>
#include <vector>
//#include <gl/GL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TGLInventory.h"

namespace useful_structures
{
	extern std::map<TGLItemId, glm::vec2> item_id_to_texture_coords;

	extern std::vector <GLfloat> vertex_data_block_small;

	extern std::vector <GLfloat> vertex_data_block;
#ifdef _TGL_CLIENT
	TGLMesh * create_cube_mesh();
#endif

}
#endif
