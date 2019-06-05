#ifndef _ORTHOCAMERA_H_
#define _ORTHOCAMERA_H_

#include "Camera.h"

class OrthoCamera : public Camera {
    public:
        OrthoCamera();
        ~OrthoCamera();

        Ray generate_ray(float x, float y);
};

#endif