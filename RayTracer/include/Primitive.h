#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include "Ray.h"
#include "Material.h"

class SurfaceInteraction;

class Primitive {
    private:
        Material* material;
    public:
        Primitive();
        virtual ~Primitive() {};
        virtual bool intersect(Ray& r, SurfaceInteraction * si) = 0;
        virtual bool intersect_p(Ray& r ) = 0;
        virtual const Material * get_material(void) const { return material; }
        virtual const void set_material(Material* material) {this->material = material;}
}; 

#endif