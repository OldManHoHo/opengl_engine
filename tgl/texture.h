#pragma once
#ifndef TGL_TEXTURE_H_
#define TGL_TEXTURE_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include "tgl/tgl_gl.h"

namespace tgl
{

class Texture
{
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
};

}  // namespace tgl

#endif  // TGL_TEXTURE_H_
