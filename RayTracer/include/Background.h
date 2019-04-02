#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <iostream>
#include <vector>
#include <string>
#include "Color.h"

class Background {
    private:
        std::string type;
        std::vector<Color> colors;

    public:
        Background();
        ~Background();
        void set_type(std::string type);
        void add_color(Color color);
        Color get_pixel(float x, float y);
}; 

#endif