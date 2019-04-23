#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Primitive.h"

class Sphere : public Primitive {
    std::string name;
    std::string type;
    float radius;
    vec3 center;

    public: 
        Sphere();
        Sphere(std::string name, std::string type, float radius, vec3 center);
        ~Sphere();
        bool intersect(const Ray& r, SurfaceInteraction * si);
        bool intersect_p( const Ray& r );
};

#endif