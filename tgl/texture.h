#pragma once
#ifndef TGL_TEXTURE_H_
#define TGL_TEXTURE_H_

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
    explicit Texture(char * filename);
    ~Texture();
    GLuint get_name();
};

}  // namespace tgl

#endif  // TGL_TEXTURE_H_
