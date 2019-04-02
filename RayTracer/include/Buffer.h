#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "Color.h"

class Buffer {
    private:
        Color * canvas;
        unsigned int width;
        unsigned int height;
        bool anti_aliasing; 

    public:
        Buffer();
        Buffer(unsigned int width, unsigned int height);
        ~Buffer();
        void set_size(unsigned int width, unsigned int height);
        unsigned int get_width();
        unsigned int get_height();
        Color * get_canvas();
        void draw_background(Color bg_color);
        void draw_pixel(int x, int y, Color color);
        Color get_pixel(int x, int y);
};

#endif