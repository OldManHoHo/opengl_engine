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

#endif /* defined(__TGL_Server__TGLGameState__) */
