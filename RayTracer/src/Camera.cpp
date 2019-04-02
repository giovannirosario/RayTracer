#include "Camera.h"

Camera::Camera() {}

void Camera::set_size(int width, int height){
    this->width = width;
    this->height = height;
}

void Camera::set_type(std::string type){
    this->type = type;
}

int Camera::get_width() {
    return this->width;
}

int Camera::get_height() {
    return this->height;
}

