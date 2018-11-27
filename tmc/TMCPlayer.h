#ifndef _TMCPlayer
#define _TMCPlayer

#include "TGLChunkSpawn.h"

class TMCPlayer : public TGLPlayer
{
    TGLChunkSpawn * chunk_spawn;
    
public:
    void tick(double time_delta);
    void set_chunk_spawn(TGLChunkSpawn * in_chunk_spawn);
};

#endif