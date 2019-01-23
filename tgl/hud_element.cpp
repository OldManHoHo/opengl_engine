#include <iostream>

#include "tgl/hud_element.h"

namespace tgl
{

FT_Library HudElement::library;
FT_Face HudElement::face;
std::map<char, Texture*> HudElement::char_textures;
float HudElement::font_size;

void HudElement::init_ft_library()
{
    int in_height = 75;
    font_size = in_height;
    int error = FT_Init_FreeType(&library);
    if (error)
    {
        std::cout << "FT init error." << "\n";
    }

    error = FT_New_Face(library,
        "content/fonts/helvetica.ttf",
        0,
        &face);
    if (error == FT_Err_Unknown_File_Format)
    {
        std::cout << "FT unknown file format" << "\n";
    }
    else if (error)
    {
        std::cout << "Other error" << "\n";
    }

    FT_GlyphSlot  slot = HudElement::face->glyph;  /* a small shortcut */
    int           pen_x, pen_y, n;
    int num_chars = sizeof(text) - 1;
    std::string alpha_text = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

    error = FT_Set_Pixel_Sizes(
        face,   /* handle to face object */
        0,      /* pixel_width           */
        in_height);   /* pixel_height          */

    pen_x = 300;
    pen_y = 200;
    //tex = new Texture(&HudElement::face->glyph->bitmap,
    //    pen_x + slot->bitmap_left,
    //    pen_y - slot->bitmap_top);
    for (n = 0; n < alpha_text.size(); n++)
    {
        //HudElement * sub_glyph = new HudElement(in_height, in_height, in_color, glm::vec2(in_height*n, 0));

        FT_UInt  glyph_index;

        /* retrieve glyph index from character code */
        glyph_index = FT_Get_Char_Index(HudElement::face, alpha_text[n]);

        /* load glyph image into the slot (erase previous one) */
        error = FT_Load_Glyph(HudElement::face, glyph_index, FT_LOAD_DEFAULT);
        if (error)
            continue;  /* ignore errors */

            /* convert to an anti-aliased bitmap */
        error = FT_Render_Glyph(HudElement::face->glyph, FT_RENDER_MODE_NORMAL);
        if (error)
            continue;

        Texture * tex = new Texture(&HudElement::face->glyph->bitmap,
            pen_x + slot->bitmap_left,
            pen_y - slot->bitmap_top);
        char_textures[alpha_text[n]] = tex;
        /* now, draw to our target surface */
        //my_draw_bitmap(&slot->bitmap,
        //    pen_x + slot->bitmap_left,
        //    pen_y - slot->bitmap_top);

        /* increment pen position */
        //pen_x += slot->advance.x >> 6;
        //pen_y += slot->advance.y >> 6; /* not useful for now */
        //sub_elements.push_back(sub_glyph);
    }
}

HudElement::HudElement(
    ::GLfloat in_width,
    ::GLfloat in_height,
    glm::vec3 in_color,
    ::glm::vec2 in_pos
    ) :
        params(4),
        texture_active(false),
        top_left_tex_offset(0.001, 0.001),
        bottom_right_tex_offset(0, 0),
        visible(true)
{
    texture_active = true;
    hud_shader_f = new Shader(
        "content/shaders/fragment_shader_HUD_text.glsl",
        GL_FRAGMENT_SHADER);
    hud_shader_v = new Shader(
        "content/shaders/vertex_shader_HUD_text.glsl",
        GL_VERTEX_SHADER);


    if (bottom_right_tex_offset.x != 0 && bottom_right_tex_offset.y != 0)
    {
        top_left_tex_offset.x = top_left_tex_offset.x / tex->width;
        top_left_tex_offset.y = top_left_tex_offset.y / tex->height;
        bottom_right_tex_offset.x = bottom_right_tex_offset.x / tex->width;
        bottom_right_tex_offset.y = bottom_right_tex_offset.y / tex->height;
    }
    else
    {
        bottom_right_tex_offset.x = 0.999;
        bottom_right_tex_offset.y = 0.999;
    }

    height = in_height;
    width = in_width;
    pos = in_pos;
    color = in_color;
    mat.add_shader(hud_shader_v);
    mat.add_shader(hud_shader_f);

    mat.link_shader();
}

HudElement::HudElement(
    ::GLfloat in_width,
    ::GLfloat in_height,
    ::glm::vec2 in_pos,
    ::glm::vec3 in_color,
    std::string in_text,
    int top_left_tex_offset_x,
    int top_left_tex_offset_y,
    int bottom_right_tex_offset_x,
    int bottom_right_tex_offset_y) :
        params(4),
        texture_active(false),
        top_left_tex_offset(0.001, 0.001),
        bottom_right_tex_offset(bottom_right_tex_offset_x,
            bottom_right_tex_offset_y),
        visible(true)
{
    int           pen_x, pen_y, n;
    int error;
    int num_chars = sizeof(text)-1;
    text = in_text;

    error = FT_Set_Pixel_Sizes(
        face,   /* handle to face object */
        0,      /* pixel_width           */
        in_height);   /* pixel_height          */

    pen_x = 300;
    pen_y = 200;
    int cursor = 0;
    //tex = new Texture(&HudElement::face->glyph->bitmap,
    //    pen_x + slot->bitmap_left,
    //    pen_y - slot->bitmap_top);
    for (n = 0; n < text.size(); n++)
    {
        Texture * char_tex = char_textures[text[n]];
        HudElement * sub_glyph = new HudElement(int(in_height*1.4*char_tex->width/font_size),
            int(in_height*char_tex->height / font_size),
            in_color, glm::vec2(cursor + (in_height*0.8/2 - int(in_height*1.4*char_tex->width / font_size)/2), 0));
        sub_glyph->tex = char_tex;
        cursor += in_height*0.8;
        /* now, draw to our target surface */
        //my_draw_bitmap(&slot->bitmap,
        //    pen_x + slot->bitmap_left,
        //    pen_y - slot->bitmap_top);

        /* increment pen position */
        //pen_x += slot->advance.x >> 6;
        //pen_y += slot->advance.y >> 6; /* not useful for now */
        sub_elements.push_back(sub_glyph);
    }

    texture_active = false;
    hud_shader_f = new Shader(
        "content/shaders/fragment_shader_HUD.glsl",
        GL_FRAGMENT_SHADER);
    hud_shader_v = new Shader(
        "content/shaders/vertex_shader_HUD.glsl",
        GL_VERTEX_SHADER);

    if (bottom_right_tex_offset.x != 0 && bottom_right_tex_offset.y != 0)
    {
        top_left_tex_offset.x = top_left_tex_offset.x / tex->width;
        top_left_tex_offset.y = top_left_tex_offset.y / tex->height;
        bottom_right_tex_offset.x = bottom_right_tex_offset.x / tex->width;
        bottom_right_tex_offset.y = bottom_right_tex_offset.y / tex->height;
    }
    else
    {
        bottom_right_tex_offset.x = 0.999;
        bottom_right_tex_offset.y = 0.999;
    }

    height = in_height;
    width = 0;
    color = in_color;
    pos = in_pos;
    mat.add_shader(hud_shader_v);
    mat.add_shader(hud_shader_f);

    mat.link_shader();
}

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
		                        bottom_right_tex_offset_y),
        visible(true)
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

void HudElement::set_text(std::string in_text)
{
    text = in_text;
    int cursor = 0;
    for (auto se : sub_elements)
    {
        delete se;
    }
    sub_elements.clear();
    for (int n = 0; n < text.size(); n++)
    {
        HudElement * sub_glyph;
        Texture * char_tex = char_textures[text[n]];
        if (n >= sub_elements.size())
        {
            
            sub_glyph = new HudElement(int(height*1.4*char_tex->width / font_size),
                int(height*char_tex->height / font_size),
                color, glm::vec2(cursor + (height*0.8 / 2 - int(height*1.4*char_tex->width / font_size) / 2), 0));
        }
        else
        {
            sub_glyph = sub_elements[n];
            sub_glyph->height = int(height*char_tex->height / font_size);
            sub_glyph->width = int(height*1.4*char_tex->width / font_size);
        }
        sub_glyph->tex = char_tex;
        cursor += height * 0.8;
        /* now, draw to our target surface */
        //my_draw_bitmap(&slot->bitmap,
        //    pen_x + slot->bitmap_left,
        //    pen_y - slot->bitmap_top);

        /* increment pen position */
        //pen_x += slot->advance.x >> 6;
        //pen_y += slot->advance.y >> 6; /* not useful for now */
        sub_elements.push_back(sub_glyph);
    }
}

}  // namespace tgl