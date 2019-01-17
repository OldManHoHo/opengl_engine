#ifndef TGL_NET_MESSAGES_H_
#define TGL_NET_MESSAGES_H_

namespace tgl
{

enum NetMsgType
{
    Heartbeat,
    GameState,
    PlayerInput,
    ChunkRequest,
    ChunkUpdate
};

}  // namespace tgl

#endif  // TGL_NET_MESSAGES_H_