#ifndef _ORTHOCAMERA_H_
#define _ORTHOCAMERA_H_

#include "Camera.h"

class OrthoCamera : public Camera {
    private:
        /*View plane dimensions */ 
        float l; //left
        float r; //right
        float b; //bottom
        float t; //top

    public:
        OrthoCamera();
        Ray generate_ray(int x, int y);
        Ray generate_ray(float x, float y);
};

#endif