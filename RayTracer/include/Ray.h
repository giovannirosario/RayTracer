#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h"

class Ray {
    private:
        vec3 origin; //!< origin
        vec3 v_direction; //!< direction
        
    public:
        Ray();
        Ray (vec3 o, vec3 d);
        vec3 get_origin();
        vec3 get_vDirection();
};


#endif