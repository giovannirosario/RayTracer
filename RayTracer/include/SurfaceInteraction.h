#ifndef _SURFACEINTERACTION_H_
#define _SURFACEINTERACTION_H_

#include "vec3.h"
#include "Primitive.h"

class SurfaceInteraction {
    public:
        vec3 contact_point; // Contact point.
        vec3 normal; // The surface normal.
        vec3 w; // Outgoing direction of light, which is -ray.
        float time; // Time of contact.
        vec3 uv; // Parametric coordinate (u,v) of the hit surface.
        Primitive *primitive; // Pointer to the primitive.
        
        SurfaceInteraction(){};
        SurfaceInteraction(const vec3& contact_point,const vec3& normal, const vec3& w, float time,
            vec3& uv, Primitive * primitive );
};

#endif