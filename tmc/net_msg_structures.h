#ifndef TMC_NET_MSG_STRUCTURES_H_
#define TMC_NET_MSG_STRUCTURES_H_

namespace tmc
{
namespace net_messages
{

struct Heartbeat
{
    char msg_type;
    Heartbeat()
    {
        msg_type = 0;
    }
};

struct GameState
{
    struct Header
    {
        char msg_type;
        short active_actor_id;
    };
    
    struct ActorHeader
    {
        short actor_id;
        short actor_type;
        GLfloat actor_pos[3];
        GLfloat actor_rot[16];
        GLfloat actor_scale[3];
    };
    
    struct IntProp
    {
        short int_prop_id;
        int int_prop_val;
    };
    
    struct FloatProp
    {
        short float_prop_id;
        float float_prop_val;
    };
    
    struct Vec3Prop
    {
        short vec3_prop_id;
        GLfloat vec3_prop_val[3];
    };
    
    struct ActorInfo
    {
        ActorHeader actor_header;
        short num_int_props;
        std::vector <IntProp> int_props;
        short num_float_props;
        std::vector <FloatProp> float_props;
        short num_vec3_props;
        std::vector <Vec3Prop> vec3_props;
    };
    
    struct BlockChange
    {
        e_block_type block_type;
        float x_pos;
        float y_pos;
        float z_pos;
    };
    
    Header header;
    std::vector <ActorInfo> actor_infos;
    std::vector <BlockChange> block_changes;
    
    GameState(std::vector <char>& in_buf)
    {
        int offset = 0;
        header = *reinterpret_cast<Header*>(&in_buf[offset]);
        offset += sizeof(Header);
        short num_actors = *reinterpret_cast<short*>(&in_buf[offset]);
        for (int i = 0; i < num_actors; ++i)
        {
            actor_infos.push_back(
                *reinterpret_cast<ActorInfo*>(&in_buf[offset]));
            offset += sizeof(ActorInfo);
        }
        short num_block_changes = *reinterpret_cast<short*>(&in_buf[offset]);
        for (int i = 0; i < num_block_changes; ++i)
        {
            block_changes.push_back(*reinterpret_cast<BlockChange*>(
                &in_buf[offset]));
            offset += sizeof(BlockChange);
        }
    }
    
    void gen(std::vector <char>& in_buf)
    {
        in_buf.resize(1460);
        int offset = 0;
        *reinterpret_cast<Header*>(&in_buf[offset]) = header;
        offset += sizeof(Header);
        *reinterpret_cast<short*>(&in_buf[offset]) = actor_infos.size();
        for (int i = 0; i < actor_infos.size(); ++i)
        {
            *reinterpret_cast<ActorInfo*>(&in_buf[offset]) = actor_infos[i];
            offset += sizeof(ActorInfo);
        }
        *reinterpret_cast<short*>(&in_buf[offset]) = block_changes.size();
        for (int i = 0; i < block_changes.size(); ++i)
        {
            *reinterpret_cast<BlockChange*>(&in_buf[offset]) = block_changes[i];
            offset += sizeof(BlockChange);
        }
        in_buf.resize(offset);
    }
};

struct PlayerInput
{
    struct Header
    {
        char msg_type;
        char equipped_index;
        GLfloat player_rot[16];
    };
    
    struct KeyState
    {
        char key;
        char key_state;
    };
    
    Header header;
    std::vector <KeyState> key_states;
    
    PlayerInput(std::vector <char>& in_buf)
    {
        int offset = 0;
        header = *reinterpret_cast<Header*>(&in_buf[offset]);
        offset += sizeof(Header);
        short num_key_states = *reinterpret_cast<short*>(&in_buf[offset]);
        for (int i = 0; i < num_key_states; ++i)
        {
            key_states.push_back(
                *reinterpret_cast<KeyState*>(&in_buf[offset]));
            offset += sizeof(KeyState);
        }
    }
    
    void gen(std::vector <char>& in_buf)
    {
        in_buf.resize(1460);
        int offset = 0;
        *reinterpret_cast<Header*>(&in_buf[offset]) = header;
        offset += sizeof(Header);
        *reinterpret_cast<short*>(&in_buf[offset]) = key_states.size();
        for (int i = 0; i < key_states.size(); ++i)
        {
            *reinterpret_cast<KeyState*>(&in_buf[offset]) = key_states[i];
            offset += sizeof(KeyState);
        }
        in_buf.resize(offset);
    }
};
    
}  // namespace net_messages
}  // namespace tmc

#endif  // TMC_NET_MSG_STRUCTURES_H_

