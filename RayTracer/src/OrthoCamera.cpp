#include "OrthoCamera.h"
#include "vec3.h"

#include <iostream>

OrthoCamera::OrthoCamera() {}

OrthoCamera::~OrthoCamera() {}

Ray OrthoCamera::generate_ray(float x, float y) {
    float u = l + (r - l) * (x + 0.5)/width;
    float v = b + (t - b) * (y + 0.5)/height;
    
    vec3 ray_direction = target - position; //camera look
    vec3 w = -ray_direction;
    w.make_unit_vector();
    vec3 vec_u = cross(up, w);
    vec_u.make_unit_vector();
    vec3 vec_v = cross(w, vec_u);
    vec_v.make_unit_vector();

    vec3 ray_origin = position;
    ray_origin += vec_u * u + vec_v*v;
    //std::cout << ray_origin << "__" << ray_direction << std::endl;

    return Ray(ray_origin, ray_direction);
}