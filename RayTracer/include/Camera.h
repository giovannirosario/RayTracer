#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <string>

class Camera {
    private:
        std::string type;
        int width;
        int height;
    public:
        Camera();
        void set_size(int width, int height);
        void set_type(std::string type);
        int get_width();
        int get_height();
        

};

#endif