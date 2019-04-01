#ifndef _COLOR_H_
#define _COLOR_H_

class Color {
    private:
        unsigned char rgb[3];

    public:
        Color();
        Color(unsigned char red, unsigned char green, unsigned char blue);
        ~Color();
        void set(unsigned char red, unsigned char green, unsigned char blue);
        unsigned char get_r();
        unsigned char get_g();
        unsigned char get_b();
        Color operator=(const Color &color);
        bool operator==(const Color &color);
};  

#endif