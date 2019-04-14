#include "Camera.h"

Ray Camera::generate_ray(float x, float y) {
}

void Camera::set_size(int width, int height){
    this->width = width;
    this->height = height;
}

int Camera::get_width() {
    return this->width;
}

int Camera::get_height() {
    return this->height;
}

void Camera::set_position(vec3 position){
    this->position = position;
}

void Camera::set_target(vec3 target){
    this->target = target;
}

void Camera::set_up(vec3 up){
    this->up = up;
}

