#include "Sphere.h"
#include "SurfaceInteraction.h"

Sphere::Sphere() {}

Sphere::Sphere(PrimitiveParams params){
    this->name = params.name;
    this->type = params.type;
    this->radius = params.radius;
    this->center = params.center;
}

Sphere::~Sphere(){}

bool Sphere::intersect(Ray& r, SurfaceInteraction * si)  {
}

bool Sphere::intersect_p(Ray& r ) {
    vec3 oc = r.get_origin() - this->center;
    float a = dot(r.get_vDirection(), r.get_vDirection());
    float b = 2.0 * dot(oc, r.get_vDirection());
    float c = dot(oc,oc) - this->radius * this->radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant>0);
}