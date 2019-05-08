#ifndef _CAMERAPARAMS_H_
#define _CAMERAPARAMS_H_

#include <string>
#include "vec3.h"

using namespace std;

class CameraParams {
    public:
        string type;
        vec3 position;
        vec3 target;
        vec3 up;
        float vpdim[4];
        float fovy;
        float aspect;
        float fdistance;
        int width = 800;
        int height = 600;

        CameraParams(){};
        ~CameraParams(){};
};


#endif