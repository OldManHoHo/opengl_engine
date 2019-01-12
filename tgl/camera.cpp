#include "tgl/camera.h"

#include <iostream>

namespace tgl
{

Camera::Camera()
{
    // projection = glm::perspective(glm::radians(45.0f),
    //                               screenWidth / screenHeight,
    //                               0.1f,
    //                               100.0f);
    translate(glm::vec3(10.0, 180.0, 10.0));
    // set_transform(glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
    //  glm::vec3(0.0f, 0.0f, 0.0f),
    //  glm::vec3(0.0f, 1.0f, 0.0f)));
}

Camera::~Camera()
{
}

void Camera::set_projection(glm::mat4 in_mat)
{
    projection = in_mat;
}

glm::mat4 Camera::get_projection()
{
    return projection;
}

glm::mat4 Camera::get_view()
{
    glm::vec3 forward(1.0f, 0.0f, 0.0f);
    forward = glm::mat3(get_rot())*forward;
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    up = glm::mat3(get_rot())*up;
    eye_loc = get_pos() + up*static_cast<float>(1.65 - 1.85 / 2);
    view = glm::lookAt(eye_loc, eye_loc + forward, up);
    return view;
}

void Camera::set_view(glm::mat4 in_view)
{
    view = in_view;
}

void Camera::tick(double time_delta)
{
}

}  // namespace tgl
