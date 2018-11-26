#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TGLShader.h"
#include "TGLMaterial.h"


class TGLHudElement
{


public:
	bool texture_active;
	GLfloat height;
	GLfloat width;
	glm::vec3 color;
	glm::vec2 pos;
	std::vector <GLfloat> params;
	std::vector <TGLHudElement*> sub_elements;

	TGLTexture * tex;
	TGLMaterial mat;
	TGLShader * hud_shader_f;
	TGLShader * hud_shader_v;

	TGLHudElement(GLfloat in_width, GLfloat in_height, glm::vec2 in_pos, glm::vec3 in_color, char * texture_file = nullptr);

	GLfloat * get_params();

};