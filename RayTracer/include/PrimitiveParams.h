#ifndef _PRIMITIVEPARAMS_H_
#define _PRIMITIVEPARAMS_H_

#include <iostream>
#include "vec3.h"

class PrimitiveParams {
    public:
        std::string name;
        std::string type;
        float radius;
        vec3 center;
        
        PrimitiveParams(){};
        ~PrimitiveParams(){};
};

#endif