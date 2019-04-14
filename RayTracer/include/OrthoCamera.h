#ifndef _ORTHOCAMERA_H_
#define _ORTHOCAMERA_H_

#include "Camera.h"

class OrthoCamera : public Camera {
    private:

    public:
        OrthoCamera();
        ~OrthoCamera();

        Ray generate_ray(float x, float y);
};

#endif