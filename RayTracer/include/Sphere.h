#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Primitive.h"
#include "PrimitiveParams.h"

class Sphere : public Primitive {
    std::string name;
    std::string type;
    float radius;
    vec3 center;
    Material* material;

    public: 
        Sphere();
        Sphere(PrimitiveParams params);
        ~Sphere();
        bool intersect(Ray& r, SurfaceInteraction * si);
        bool intersect_p(Ray& r );
};

#endif