#include "Color.h"

Color::Color() {}

Color::Color(unsigned char red, unsigned char green, unsigned char blue) {
    this->rgb[0] = red;
    this->rgb[1] = green;
    this->rgb[2] = blue;
}

void Color::set(unsigned char red, unsigned char green, unsigned char blue) {
    this->rgb[0] = red;
    this->rgb[1] = green;
    this->rgb[2] = blue;
}

Color::~Color() {}

unsigned char Color::get_r() {
    return this->rgb[0];
}

unsigned char Color::get_g(){
    return this->rgb[1];
}

unsigned char Color::get_b(){
    return this->rgb[2];
};

Color Color::operator=(const Color &color) {
	this->rgb[0] = color.rgb[0];
    this->rgb[1] = color.rgb[1];
    this->rgb[2] = color.rgb[2];
    
    return *this;
}

bool Color::operator==(const Color &color) {
	return (this->rgb[0] == color.rgb[0] &&
            this->rgb[1] == color.rgb[1] &&
            this->rgb[2] == color.rgb[2]);
}
