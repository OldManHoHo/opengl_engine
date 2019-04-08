#pragma once
#ifndef TGL_ACTOR_H_
#define TGL_ACTOR_H_

#include <deque>
#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tgl/bounds.h"
#include "tgl/component.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>


namespace tgl
{

class PhysicsEngine;
class Base;

class Actor
{
 public:
    static int _id_counter;

 protected:
    glm::vec3 pos;
    glm::vec3 prev_pos;
    glm::vec3 vel;
    glm::vec3 accel;
    float mass;
    glm::mat4 rot;
    glm::vec3 scale;
    glm::mat4 transform;
    std::vector <std::shared_ptr<tgl::Component>> components;
 public:
    int id;
    int type;
 protected:

// NETWORK
    std::vector <double*> double_props;
    std::vector <float*> float_props;
    std::vector <char*> char_props;
    std::vector <int*> int_props;
    std::vector <glm::vec3*> vec3_props;
    std::vector <glm::mat4*> mat4_props;

    std::vector <double*> prev_double_props;
    std::vector <float*> prev_float_props;
    std::vector <char*> prev_char_props;
    std::vector <int*> prev_int_props;
    std::vector <glm::vec3*> prev_vec3_props;
    std::vector <glm::mat4*> prev_mat4_props;

    std::deque <void*> network_messsages;
// END NETWORK

    std::shared_ptr<Bounds> bounds;

    bool transform_calculated;
    bool update_transform;
    bool on_ground;
    friend class ::tgl::PhysicsEngine;
    friend class Base;

 public:
    // flags
    bool static_physics;
    bool is_chunk;
    bool delete_flag;
    
    Actor();
    Actor(glm::vec3 in_pos);
    ~Actor() = default;
    bool operator ==(const tgl::Actor &b) const;
    bool operator!=(const tgl::Actor &b) const;
    Actor(const Actor& rhs) = default;
    Actor& operator=(const Actor& rhs) = default;

    void set_transform(glm::mat4 in_transform);
    glm::mat4 get_transform();
    glm::vec3 get_pos();
    void set_pos(glm::vec3 in_pos);
    glm::mat4 get_rot();
    void set_rot(glm::mat4 in_rot);
    glm::vec3 get_scale();
    void set_scale(glm::vec3 in_scale);
    void add_component(tgl::Component * in_component);
    std::vector <std::shared_ptr<tgl::Component>> get_components();
    void flag_for_deletion(bool do_delete);
    virtual void tick(double time_delta);
    void translate(glm::vec3 in_translation);
    void rotate(float angle, glm::vec3 axis);
    void set_bounds(Bounds * in_bounds);
    std::shared_ptr<Bounds> get_bounds();
    void set_on_ground(bool in_on_ground);
    bool get_on_ground();

    friend class cereal::access;
    template<class Archive> 
    void serialize(Archive & archive) 
    { 
        archive( pos.x, pos.y, pos.z, id, mass, type ); // serialize things by passing them to the archive
        for (int i = 0; i < 16; ++i)
        {
            archive( *(glm::value_ptr(rot) + i) );
        }
        //archive( cereal::binary_data(glm::value_ptr(rot), 16*sizeof(float)));
    }
    
    void register_network_property(double * in_prop);
    void register_network_property(float * in_prop);
    void register_network_property(char * in_prop);
    void register_network_property(int * in_prop);
    void register_network_property(unsigned int * in_prop);

    void queue_network_message(void * in_message);
};

}  // namespace tgl

#endif  // TGL_ACTOR_H_
