#ifndef _FLATMATERIAL_H_
#define _FLATMATERIAL_H_

#include "Camera.h"
#include "Material.h"

class FlatMaterial : public Material {
    private:

    public:
        FlatMaterial(){};
        FlatMaterial(std::string name, std::string type, Color color, std::string color_type){
            this->name = name;
            this->type = type;
            this->color = color;
            this->color_type = color_type;
        };
        ~FlatMaterial(){};
};

#endif