#include "PerspectiveCamera.h"
#include <math.h>

PerspectiveCamera::PerspectiveCamera() {}

PerspectiveCamera::~PerspectiveCamera() {}

Ray PerspectiveCamera::generate_ray(float x, float y) {
    float half_height = tan(fovy /2) * fdistance;
    float half_width = aspect * half_height;
    l = -half_width;
    r = half_width;
    b = -half_height;
    t = half_height;

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