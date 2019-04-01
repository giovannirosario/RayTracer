#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera {
    private:
        int width;
        int height;
    public:
        Camera();
        void set_size(int width, int height);
};

#endif