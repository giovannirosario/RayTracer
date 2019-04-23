#ifndef _SURFACEINTERACTION_H_
#define _SURFACEINTERACTION_H_

#include "vec3.h"
#include "Primitive.h"

class SurfaceInteraction {
    private:
        vec3 contatct_point; // Contact point.
        vec3 normal; // The surface normal.
        vec3 w; // Outgoing direction of light, which is -ray.
        float time; // Time of contact.
        const vec3 uv; // Parametric coordinate (u,v) of the hit surface.
        const Primitive *primitive; // Pointer to the primitive.

    public:
        SurfaceInteraction(const vec3& contact_point,const vec3& normal, const vec3& w, float time,
            const vec3& uv, const Primitive * primitive );
};

#endif