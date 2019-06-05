#ifndef _PERSPECTIVECAMERA_H_
#define _PERSPECTIVECAMERA_H_

#include "Camera.h"
#include "Ray.h"

class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera();
        ~PerspectiveCamera();

        Ray generate_ray(float x, float y);
};

#endif