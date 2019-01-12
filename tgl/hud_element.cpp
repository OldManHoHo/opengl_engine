#include "tgl/hud_element.h"

namespace tgl
{

HudElement::HudElement(
    ::GLfloat in_width,
	::GLfloat in_height,
	::glm::vec2 in_pos,
	::glm::vec3 in_color,
	const char * texture_file,
	int top_left_tex_offset_x,
	int top_left_tex_offset_y,
	int bottom_right_tex_offset_x,
	int bottom_right_tex_offset_y) :
	    params(4),
	    texture_active(false),
	    top_left_tex_offset(top_left_tex_offset_x, top_left_tex_offset_y),
	    bottom_right_tex_offset(bottom_right_tex_offset_x,
		                        bottom_right_tex_offset_y)
{
	if (texture_file != nullptr)
	{
		tex = new Texture(texture_file);
		texture_active = true;
		hud_shader_f = new Shader(
			"content/shaders/fragment_shader_HUD_tex.glsl",
			GL_FRAGMENT_SHADER);
		hud_shader_v = new Shader(
			"content/shaders/vertex_shader_HUD_tex.glsl",
			GL_VERTEX_SHADER);
	}
	else
	{
		hud_shader_f = new Shader(
			"content/shaders/fragment_shader_HUD.glsl",
			GL_FRAGMENT_SHADER);
		hud_shader_v = new Shader(
			"content/shaders/vertex_shader_HUD.glsl",
			GL_VERTEX_SHADER);
	}

	if (bottom_right_tex_offset.x != 0 && bottom_right_tex_offset.y != 0)
	{
		top_left_tex_offset.x = top_left_tex_offset.x / tex->width;
		top_left_tex_offset.y = top_left_tex_offset.y / tex->height;
		bottom_right_tex_offset.x = bottom_right_tex_offset.x / tex->width;
		bottom_right_tex_offset.y = bottom_right_tex_offset.y / tex->height;
	}
	else
	{
		bottom_right_tex_offset.x = 1.0;
		bottom_right_tex_offset.y = 1.0;
	}

	height = in_height;
	width = in_width;
	color = in_color;
	pos = in_pos;
    mat.add_shader(hud_shader_v);
	mat.add_shader(hud_shader_f);

	mat.link_shader();
}

::GLfloat * HudElement::get_params()
{
	params[0] = width;
	params[1] = height;
	params[2] = pos.x;
	params[3] = pos.y;
	return &params[0];
}

void HudElement::set_offsets(::glm::vec2 top_left, ::glm::vec2 bottom_right)
{
	bottom_right_tex_offset = bottom_right;
	top_left_tex_offset = top_left;
	top_left_tex_offset.x = top_left_tex_offset.x / tex->width;
	top_left_tex_offset.y = top_left_tex_offset.y / tex->height;
	bottom_right_tex_offset.x = bottom_right_tex_offset.x / tex->width;
	bottom_right_tex_offset.y = bottom_right_tex_offset.y / tex->height;
}

}  // namespace tgl