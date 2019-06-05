#include "PerspectiveCamera.h"
#include <math.h>

PerspectiveCamera::PerspectiveCamera() {}

PerspectiveCamera::~PerspectiveCamera() {}

Ray PerspectiveCamera::generate_ray(float x, float y) {
    float u = l + (r - l) * (x + 0.5)/width;
    float v = b + (t - b) * (y + 0.5)/height;
    
    vec3 w = -(target - position);
    w.make_unit_vector();
    vec3 vec_u = cross(up, w);
    vec_u.make_unit_vector();
    vec3 vec_v = cross(w, vec_u);
    vec_v.make_unit_vector();


    vec3 ray_direction = -fdistance * w +  vec_u*u + vec_v * v; //camera look

    vec3 ray_origin = position;

    return Ray(ray_origin, ray_direction);

}