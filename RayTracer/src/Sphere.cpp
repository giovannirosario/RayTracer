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
        vec3 origin = r.get_origin();
        vec3 direction = r.get_vDirection();

        vec3 oc = r.get_origin() - this->center;
        
        float a = dot(r.get_vDirection(), r.get_vDirection());
        float b = 2.0 * dot(oc, r.get_vDirection());
        float c = dot(oc,oc) - this->radius * this->radius;
        
        float discriminant = b*b - 4*a*c;
        
        if (discriminant < 0.0) {
            return false;
        }
        else {
            float x1 = (-b + sqrt(discriminant)) / (2 * a);
            float x2 = (-b - sqrt(discriminant)) / (2 * a);

            si->time = fmin(x1,x2);
            si->contact_point = origin + (si->time * direction);
            si->primitive->set_material(this->material);
            auto n = unit_vector(si->contact_point - center);
            si->normal = 0.5 * vec3(n.x()+1, n.y()+1, n.z()+1); //normal

            return true;
        }
}

bool Sphere::intersect_p(Ray& r ) {
    vec3 oc = r.get_origin() - this->center;
    float a = dot(r.get_vDirection(), r.get_vDirection());
    float b = 2.0 * dot(oc, r.get_vDirection());
    float c = dot(oc,oc) - this->radius * this->radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant>0);
}