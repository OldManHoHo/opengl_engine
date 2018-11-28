#include "useful_structures.h"

namespace useful_structures
{
	extern std::map<TGLItemId, glm::vec2> item_id_to_texture_coords = {
		{ iid_dirt_with_grass_block, glm::vec2(0,16)},
		{ iid_dirt_block, glm::vec2(16*2,16) },
		{ iid_stone_block, glm::vec2(16,16) },
		{ iid_tree_block, glm::vec2(0,0) },
		{ iid_leaves_block, glm::vec2(0,0) },
		{ iid_water_block, glm::vec2(0,0) },
		{ iid_sand_block, glm::vec2(16*2,16*2) }
	};

	extern std::vector <GLfloat> vertex_data_block_small = {
		-0.5f, -0.5f, 0.5f, //(0,-1,0)
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,

		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,

		-0.5f, 0.5f, -0.5f, //(-1,0,0)
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,

		0.5f, 0.5f, -0.5f, //(0,0,-1)
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,

		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, 0.5f, 0.5f, //(0,1,0)
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f, //(1,0,0)
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, 0.5f, //(0,0,1)
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
	};


	extern std::vector <GLfloat> vertex_data_block = {
		-1.0f,-1.0f,1.0f, //(0,-1,0)
		1.0f,-1.0f,1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,1.0f,-1.0f, //(-1,0,0)
		-1.0f,1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		-1.0f,1.0f,-1.0f,
		-1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,1.0f,-1.0f, //(0,0,-1)
		-1.0f,1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,1.0f,1.0f, //(0,1,0)
		1.0f,1.0f,1.0f,
		1.0f,1.0f,-1.0f,
		-1.0f,1.0f,1.0f,
		1.0f,1.0f,-1.0f,
		-1.0f,1.0f,-1.0f,
		1.0f,1.0f,-1.0f, //(1,0,0)
		1.0f,1.0f,1.0f,
		1.0f,-1.0f,1.0f,
		1.0f,1.0f,-1.0f,
		1.0f,-1.0f,1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f,1.0f,1.0f, //(0,0,1)
		-1.0f,1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		1.0f,1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		1.0f,-1.0f,1.0f,
	};
#ifdef _TGL_CLIENT
	TGLMesh * create_cube_mesh()
	{
		TGLMeshVertices * block_mesh_vertices = new TGLMeshVertices(useful_structures::vertex_data_block_small);
		TGLMesh * temp_mesh = new TGLMesh(block_mesh_vertices);
		TGLMaterial * temp_mat = new TGLMaterial();


		TGLShader v_shader("vertex_shader.glsl", GL_VERTEX_SHADER);
		TGLShader f_shader("fragment_shader.glsl", GL_FRAGMENT_SHADER);

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			printf("GL ERROR: %d\n", err);
		}

		temp_mat->add_shader(&v_shader);
		temp_mat->add_shader(&f_shader);
		temp_mat->link_shader();

		//temp_mesh->set_material(block_material, 0);
		temp_mesh->set_material(temp_mat);

		return temp_mesh;
	}
#endif
}