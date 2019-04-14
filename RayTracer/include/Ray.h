#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h"

class Ray {
    private:
        const vec3 origin; //!< origin
        const vec3 v_direction; //!< direction
        
    public:
        Ray();
        Ray (const vec3& o, const vec3& d ) : origin{origin}, v_direction{v_direction} {}
};


#endif