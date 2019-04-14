#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <string>
#include "Ray.h"

class Camera {
    protected:
        int width;
        int height;
        vec3 position;
        vec3 target;
        vec3 up;

    public:
        Camera();
        void set_size(int width, int height);
        void set_position(vec3 position);
        void set_target(vec3 target);
        void set_up(vec3 up);
        int get_width();
        int get_height();

        virtual Ray generate_ray(int x, int y) = 0;
        virtual Ray generate_ray(float x, float y) = 0;
        

};

#endif