//
//  TGLGameState.h
//  TGL_Server
//
//  Created by Teddy Walsh on 12/17/18.
//
//

#ifndef __TGL_Server__TGLGameState__
#define __TGL_Server__TGLGameState__

#include <stdio.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef unsigned int TGLActorType;

enum TGLNetMsgType
{
    Heartbeat,
    GameState,
    PlayerInput
};

class TGLProperty
{
public:
    char prop_id;
    union prop_val
    {
        int int_val;
        float float_val;
        glm::vec3 vec_val;
    };
};

class TGLActorState
{
public:
    int id;
    TGLActorType type;
    glm::mat4 transform;
    std::vector <TGLProperty> props;
};

class TGLGameState
{
public:
    std::vector <TGLActorState> actor_states;
};


// char packet_type
// short num_actors
//     short actor_id
//     short actor_type
//     glm::mat4 transform
//     short num_int_props
//         short int_prop_id
//         int int_prop_val
//     short num_float_props
//         short float_prop_id
//         float int_prop_val
//     short num_vec3_props
//         short vec3_prop_id
//         vec3 vec3_prop_val


#endif /* defined(__TGL_Server__TGLGameState__) */
