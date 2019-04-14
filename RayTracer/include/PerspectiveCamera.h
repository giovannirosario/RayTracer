#ifndef _PERSPECTIVECAMERA_H_
#define _PERSPECTIVECAMERA_H_

#include "Camera.h"
#include "Ray.h"

class PerspectiveCamera : public Camera {
    private:
        float fovy;
        float aspect;
        float fdistance;

    public:
        PerspectiveCamera();
        ~PerspectiveCamera();

        Ray generate_ray(float x, float y);
};

#endif