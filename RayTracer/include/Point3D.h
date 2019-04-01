#ifndef _POINT3D_H_
#define _POINT3D_H_

#include <math.h>
#include <stdlib.h>
#include <iostream>

class Point3D  {
    public:
        float e[3];
        Point3D() {}
        Point3D(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
        inline const Point3D& operator+() const { return *this; }
        inline Point3D operator-() const { return Point3D(-e[0], -e[1], -e[2]); }
        inline float operator[](int i) const { return e[i]; }
        inline float& operator[](int i) { return e[i]; };
        inline Point3D& operator+=(const Point3D &v2);
        inline Point3D& operator-=(const Point3D &v2);
        inline Point3D& operator*=(const Point3D &v2);
        inline Point3D& operator/=(const Point3D &v2);
        inline Point3D& operator*=(const float t);
        inline Point3D& operator/=(const float t);
    
        inline float length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
        inline float squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
        inline void make_unit_vector();
};

#endif