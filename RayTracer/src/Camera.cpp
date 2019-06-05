#include "Camera.h"

Ray Camera::generate_ray(float x, float y) {}

int Camera::get_width() {
    return this->width;
}

int Camera::get_height() {
    return this->height;
}

void Camera::set_params(CameraParams params) {
    this->width = params.width;
    this->height = params.height;

    this->film.set_size(this->width, this->height);

    this->position = params.position;
    this->target = params.target;
    this->up = params.up;

    this->fovy = params.fovy;
    this->fdistance = params.fdistance;
    this->aspect = params.aspect;

     if(params.type == "orthographic") {
        this->l = params.vpdim[0];
        this->r = params.vpdim[1];
        this->b = params.vpdim[2];
        this->t = params.vpdim[3];
    } else if (params.type == "perspective") {
        float half_height = tan(fovy /2) * fdistance;
        float half_width = aspect * half_height;
        this->l = -half_width;
        this->r = half_width;
        this->b = -half_height;
        this->t = half_height;
    }
}