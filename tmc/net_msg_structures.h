#ifndef TMC_NET_MSG_STRUCTURES_H_
#define TMC_NET_MSG_STRUCTURES_H_

namespace tmc
{
namespace net_messages
{

template <class T>
void serialize(T in_val, char* in_buf, int& offset, int count = -1)
{
	*reinterpret_cast<T*>(&in_buf[offset]) = in_val;
	offset += sizeof(T);
}

template <class T>
void serialize_array(T* in_val, char* in_buf, int& offset, int count = -1)
{
	for (int i = 0; i < count; ++i)
	{
		*reinterpret_cast<T*>(&in_buf[offset]) = in_val[i];
		offset += sizeof(T);
	}
}

template <class T>
void deserialize(T& in_val, char* in_buf, int& offset, int count = -1)
{
	in_val = *reinterpret_cast<T*>(&in_buf[offset]);
	offset += sizeof(T);
}

template <class T>
void deserialize(T* in_val, char* in_buf, int& offset, int count = -1)
{
	for (int i = 0; i < count; ++i)
	{
		in_val[i] = *reinterpret_cast<T*>(&in_buf[offset]);
		offset += sizeof(T);
	}
}

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
		Header() : msg_type(0), active_actor_id(0) {}
		Header(char* in_buf)
		{
			int offset = 0;
			deserialize(msg_type, in_buf, offset);
			deserialize(active_actor_id, in_buf, offset);
		}
		void gen(char* in_buf)
		{
			int offset = 0;
			serialize(msg_type, in_buf, offset);
			serialize(active_actor_id, in_buf, offset);
		}
        char msg_type;
        short active_actor_id;
    };
    
    struct ActorHeader
    {
		ActorHeader() : actor_id(0), actor_type(0) {}
		ActorHeader(char* in_buf)
		{
			int offset = 0;
			deserialize(actor_id, in_buf, offset);
			deserialize(actor_type, in_buf, offset);
			deserialize_array(actor_pos, in_buf, offset, 3);
			deserialize_array(actor_rot, in_buf, offset, 16);
			deserialize_array(actor_scale, in_buf, offset, 3);
		}
		void gen(char* in_buf)
		{
			int offset = 0;
			serialize(actor_id, in_buf, offset);
			serialize(actor_type, in_buf, offset);
			serialize_array(actor_pos, in_buf, offset, 3);
			serialize_array(actor_rot, in_buf, offset, 16);
			serialize_array(actor_scale, in_buf, offset, 3);
		}
        short actor_id;
        short actor_type;
        GLfloat actor_pos[3];
        GLfloat actor_rot[16];
        GLfloat actor_scale[3];
    };
    
    struct IntProp
    {
		IntProp() : int_prop_id(0), int_prop_val(0) {}
		IntProp(char* in_buf)
		{
			int offset = 0;
			deserialize(int_prop_id, in_buf, offset);
			deserialize(int_prop_val, in_buf, offset);
		}
		void gen(char* in_buf)
		{
			int offset = 0;
			serialize(int_prop_id, in_buf, offset);
			serialize(int_prop_val, in_buf, offset);
		}
        short int_prop_id;
        int int_prop_val;
    };
    
    struct FloatProp
    {
		FloatProp() : float_prop_id(0), float_prop_val(0) {}
		FloatProp(char* in_buf)
		{
			int offset = 0;
			deserialize(float_prop_id, in_buf, offset);
			deserialize(float_prop_val, in_buf, offset);
		}
		void gen(char* in_buf)
		{
			int offset = 0;
			serialize(float_prop_id, in_buf, offset);
			serialize(float_prop_val, in_buf, offset);
		}
        short float_prop_id;
        float float_prop_val;
    };
    
    struct Vec3Prop
    {
		Vec3Prop() : vec3_prop_id(0) {}
		Vec3Prop(char* in_buf)
		{
			int offset = 0;
			deserialize(vec3_prop_id, in_buf, offset);
			deserialize_array(vec3_prop_val, in_buf, offset, 3);
		}
		void gen(char* in_buf)
		{
			int offset = 0;

			serialize(vec3_prop_id, in_buf, offset);
			serialize_array(vec3_prop_val, in_buf, offset, 3);
		}
        short vec3_prop_id;
        GLfloat vec3_prop_val[3];
    };
    
    struct ActorInfo
    {
		ActorInfo() : num_int_props(0), num_float_props(0), num_vec3_props(0) {}
		ActorInfo(char * in_buf)
		{
			int offset = 0;
			actor_header = ActorHeader(&in_buf[offset]);
			offset += sizeof(actor_header);
			deserialize(num_int_props, in_buf, offset);
			for (int i = 0; i < num_int_props; ++i)
			{
				int_props.push_back(IntProp(&in_buf[offset]));
				offset += sizeof(IntProp);
			}
			num_float_props = *reinterpret_cast<short*>(&in_buf[offset]);
			offset += sizeof(short);
			for (int i = 0; i < num_float_props; ++i)
			{
				float_props.push_back(FloatProp(&in_buf[offset]));
				offset += sizeof(FloatProp);
			}
			num_vec3_props = *reinterpret_cast<short*>(&in_buf[offset]);
			offset += sizeof(short);
			for (int i = 0; i < num_vec3_props; ++i)
			{
				vec3_props.push_back(Vec3Prop(&in_buf[offset]));
				offset += sizeof(Vec3Prop);
			}
		}
		void gen(char * in_buf)
		{
			int offset = 0;
			*reinterpret_cast<ActorHeader*>(&in_buf[offset]) = actor_header;
			offset += sizeof(ActorHeader);
			*reinterpret_cast<short*>(&in_buf[offset]) = num_int_props;
			offset += sizeof(short);
			for (auto int_prop : int_props)
			{
				*reinterpret_cast<IntProp*>(&in_buf[offset]) = int_prop;
				offset += sizeof(IntProp);
			}
			for (auto float_prop : float_props)
			{
				*reinterpret_cast<FloatProp*>(&in_buf[offset]) = float_prop;
				offset += sizeof(FloatProp);
			}
			for (auto vec3_prop : vec3_props)
			{
				*reinterpret_cast<Vec3Prop*>(&in_buf[offset]) = vec3_prop;
				offset += sizeof(Vec3Prop);
			}
		}
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
    
	GameState()
	{

	}

    GameState(std::vector <char>& in_buf)
    {
        int offset = 0;
        header = *reinterpret_cast<Header*>(&in_buf[offset]);
        offset += sizeof(Header);
        short num_actors = *reinterpret_cast<short*>(&in_buf[offset]);
		offset += sizeof(short);
        for (int i = 0; i < num_actors; ++i)
        {
            actor_infos.push_back(
                ActorInfo(&in_buf[offset]));
            offset += sizeof(ActorInfo);
        }
        short num_block_changes = *reinterpret_cast<short*>(&in_buf[offset]);
		offset += sizeof(short);
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
		offset += sizeof(short);
        for (int i = 0; i < actor_infos.size(); ++i)
        {
            //*reinterpret_cast<ActorInfo*>(&in_buf[offset]) = actor_infos[i];
			actor_infos[i].gen(&in_buf[offset]);
            offset += sizeof(ActorInfo);
        }
        *reinterpret_cast<short*>(&in_buf[offset]) = block_changes.size();
		offset += sizeof(short);
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

