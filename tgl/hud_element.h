
#ifndef TGL_HUD_ELEMENT_H_
#define TGL_HUD_ELEMENT_H_

#include <map>
#include <vector>

#ifdef _TGL_CLIENT
#include <ft2build.h>
#include FT_FREETYPE_H
#endif  // _TGL_CLIENT
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tgl/material.h"
#include "tgl/shader.h"
#include "tgl/tgl_gl.h"

namespace tgl
{

class HudElement
{
 public:
    bool texture_active;
    bool visible;
    ::GLfloat height;
    ::GLfloat width;
    ::glm::vec3 color;
    ::glm::vec2 pos;
    std::vector <::GLfloat> params;
    std::vector <HudElement*> sub_elements;
    tgl::Texture * tex;
    ::glm::vec2 top_left_tex_offset;
    ::glm::vec2 bottom_right_tex_offset;
    tgl::Material mat;
    tgl::Shader * hud_shader_f;
    tgl::Shader * hud_shader_v;
    std::string text;

#ifdef _TGL_CLIENT
    static FT_Library library;
    static FT_Face face;
    static std::map<char, Texture*> char_textures;
    static float font_size;

    static void init_ft_library();
#endif  // _TGL_CLIENT

    HudElement(
        ::GLfloat in_width,
        ::GLfloat in_height,
        glm::vec3 in_color,
        ::glm::vec2 in_pos);

    HudElement(
        ::GLfloat in_width,
        ::GLfloat in_height,
        ::glm::vec2 in_pos,
        ::glm::vec3 in_color,
        std::string in_text,
        int top_left_tex_offset_x,
        int top_left_tex_offset_y,
        int bottom_right_tex_offset_x,
        int bottom_right_tex_offset_y);

    HudElement(::GLfloat in_width,
               ::GLfloat in_height,
               ::glm::vec2 in_pos,
               ::glm::vec3 in_color,
               const char * texture_file = nullptr,
               int top_left_tex_offset_x = 0,
               int top_left_tex_offset_y = 0,
               int bottom_right_tex_offset_x = 0,
               int bottom_right_tex_offset_y = 0);

    ::GLfloat * get_params();
    void set_offsets(::glm::vec2 top_left, ::glm::vec2 bottom_right);
    void set_text(std::string in_text);
    
    virtual void on_click();
    virtual void on_click_release();
    virtual void on_drag();
};

}  // namespace tgl

#endif  // TGL_HUD_ELEMENT_H_
