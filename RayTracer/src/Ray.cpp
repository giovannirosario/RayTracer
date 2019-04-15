#include "Ray.h"

Ray::Ray(vec3 o, vec3 d ) {
    this->origin = o;
    this->v_direction = d;
}

vec3 Ray::get_origin() {
    return this->origin;
}

vec3 Ray::get_vDirection() {
    return this->v_direction;
}