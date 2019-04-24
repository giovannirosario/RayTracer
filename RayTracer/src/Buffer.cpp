#include "Buffer.h"
#include "Color.h"
#include <iostream>

Buffer::Buffer() {}

Buffer::Buffer(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    
    canvas = new Color[width * height];
}

Buffer::~Buffer() {}

void Buffer::set_size(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;;
    canvas = new Color[width * height];
}

unsigned int Buffer::get_width() {
    return this->width;
}

unsigned int Buffer::get_height() {
    return this->height;
}

Color * Buffer::get_canvas() {
    return canvas;
}

void Buffer::draw_pixel(int x, int y, Color color) {
    if(x >= 0 && y >= 0) { 
        if ((y * get_width() + x) < (get_width() * get_height())-1) {
            canvas[y * get_width() + x] = color;
        }
    }
}

Color Buffer::get_pixel(int x, int y) {
    if(x >= 0 && y >= 0) { 
        if ((y * height + x) < (width * height)-1) {
            return canvas[y * get_width() + x];
        }
    }
}

