#include "TMCPlayer.h"

void TMCPlayer::tick(double time_delta)
{
    TGLPlayer::tick(time_delta);
    
    
}

void TMCPlayer::set_chunk_spawn(TGLChunkSpawn * in_chunk_spawn)
{
    chunk_spawn = in_chunk_spawn;
}