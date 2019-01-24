#pragma once
#ifndef TGL_TEXTURE_H_
#define TGL_TEXTURE_H_

#ifdef _TGL_CLIENT
#include <ft2build.h>
#include FT_FREETYPE_H
#endif  // _TGL_CLIENT
#include "tgl/tgl_gl.h"

namespace tgl
{

class Texture
{
#ifdef _TGL_CLIENT
    static GLuint texture_count;

    int nrChannels;

 public:
    GLuint texture;
    int width;
    int height;

    GLuint texture_id;
    explicit Texture(const char * filename);
    Texture(FT_Bitmap * in_bitmap, int in_x, int in_y);
    ~Texture();
    GLuint get_name();
#endif  // _TGL_CLIENT
};

}  // namespace tgl

#endif  // TGL_TEXTURE_H_
