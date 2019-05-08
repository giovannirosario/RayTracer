#include "SurfaceInteraction.h"

#include "vec3.h"
#include "Primitive.h"

SurfaceInteraction::SurfaceInteraction(const vec3& contact_point,const vec3& normal, const vec3& w, float time,
            vec3& uv, Primitive * primitive ) {
                this->contact_point = contact_point;
                this->normal = normal;
                this->w = w;
                this->time = time;
}