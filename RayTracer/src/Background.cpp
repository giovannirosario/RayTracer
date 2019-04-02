#include "Background.h"
#include "Color.h"

Background::Background() {};
Background::~Background() {};

void Background::set_type(std::string type){
    this->type = type;
}

void Background::add_color(Color color){
    colors.push_back(color);
};

Color Background::get_pixel(float x, float y){
    if(type == "interpolation") {
        while(colors.size() != 4) {
            colors.push_back(colors.back());
        }
        int r = colors[0].get_r() * (1-x)*(1-y) + colors[1].get_r() * (1-x) * y + colors[2].get_r() * x * y + colors[3].get_r() * x * (1-y);
        int g = colors[0].get_g() * (1-x)*(1-y) + colors[1].get_g() * (1-x) * y + colors[2].get_g() * x * y + colors[3].get_g() * x * (1-y);
        int b = colors[0].get_b() * (1-x)*(1-y) + colors[1].get_b() * (1-x) * y + colors[2].get_b() * x * y + colors[3].get_b() * x * (1-y);
        return Color(r,g,b);
    }
};


