#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <string>
#include "Ray.h"
#include "CameraParams.h"
#include "Buffer.h"

class Camera {
    protected:
        int width;
        int height;
        vec3 position;
        vec3 target;
        vec3 up;

        float fovy;
        float aspect;
        float fdistance;

        /*View plane dimensions */ 
        float l; //left
        float r; //right
        float b; //bottom
        float t; //top

    public:
        Buffer film;

        Camera(){};
        virtual ~Camera(){};
        void set_params(CameraParams params);
        int get_width();
        int get_height();


        virtual Ray generate_ray(float x, float y) = 0;
};

#endif