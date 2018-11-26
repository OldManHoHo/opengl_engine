#include "TGLHudElement.h"


TGLHudElement::TGLHudElement(GLfloat in_width, GLfloat in_height, glm::vec2 in_pos, glm::vec3 in_color, char * texture_file) :
	params(4),
	texture_active(false)
{

	if (texture_file != nullptr)
	{
		tex = new TGLTexture(texture_file);
		texture_active = true;
		hud_shader_f = new TGLShader("fragment_shader_HUD_tex.glsl", GL_FRAGMENT_SHADER);
		hud_shader_v = new TGLShader("vertex_shader_HUD_tex.glsl", GL_VERTEX_SHADER);
	}
	else
	{
		hud_shader_f = new TGLShader("fragment_shader_HUD.glsl", GL_FRAGMENT_SHADER);
		hud_shader_v = new TGLShader("vertex_shader_HUD.glsl", GL_VERTEX_SHADER);
	}

	height = in_height;
	width = in_width;
	color = in_color;
	pos = in_pos;
	mat.add_shader(hud_shader_v);
	mat.add_shader(hud_shader_f);

	mat.link_shader();
}

GLfloat * TGLHudElement::get_params()
{
	params[0] = width;
	params[1] = height;
	params[2] = pos.x;
	params[3] = pos.y;
	return &params[0];
}