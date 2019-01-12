#pragma once
#ifndef TGL_COMPONENT_H_
#define TGL_COMPONENT_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// #include "tgl/actor.h"
namespace tgl
{

class Actor;  // TODO(Teddy Walsh): elim

class Component
{
    glm::mat4 transform;
    friend class Actor;

 protected:
    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;

    bool draw_flag;
    bool transform_calculated;

    Actor * parent;

 public:
    bool is_child;

    Component();
    virtual ~Component();
    void set_transform(glm::mat4 in_transform);
    glm::mat4 get_transform();
    bool get_draw_flag();
    void translate(glm::vec3 in_translation);
    void set_rot(glm::quat in_rot);
    void rotate(float angle, glm::vec3 axis);
    void set_pos(glm::vec3 in_pos);
};

}  // namespace tgl

#endif  // TGL_COMPONENT_H_
