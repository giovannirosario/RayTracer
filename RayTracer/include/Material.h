#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Color.h"
#include <iostream> 

class Material {
    public:
        std::string name;
        std::string type;
        Color color;

        Material(){};
        virtual ~Material(){};
};

#endif