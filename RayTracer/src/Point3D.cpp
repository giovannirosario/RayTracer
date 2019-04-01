#include "Point3D.h"

inline std::istream& operator>>(std::istream &is, Point3D &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Point3D &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline void Point3D::make_unit_vector() {
    float k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k; e[1] *= k; e[2] *= k;
}

inline Point3D operator+(const Point3D &v1, const Point3D &v2) {
    return Point3D(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Point3D operator-(const Point3D &v1, const Point3D &v2) {
    return Point3D(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Point3D operator*(const Point3D &v1, const Point3D &v2) {
    return Point3D(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Point3D operator/(const Point3D &v1, const Point3D &v2) {
    return Point3D(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Point3D operator*(float t, const Point3D &v) {
    return Point3D(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Point3D operator/(Point3D v, float t) {
    return Point3D(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

inline Point3D operator*(const Point3D &v, float t) {
    return Point3D(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline float dot(const Point3D &v1, const Point3D &v2) {
    return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];
}

inline Point3D cross(const Point3D &v1, const Point3D &v2) {
    return Point3D( (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}


inline Point3D& Point3D::operator+=(const Point3D &v){
    e[0]  += v.e[0];
    e[1]  += v.e[1];
    e[2]  += v.e[2];
    return *this;
}

inline Point3D& Point3D::operator*=(const Point3D &v){
    e[0]  *= v.e[0];
    e[1]  *= v.e[1];
    e[2]  *= v.e[2];
    return *this;
}

inline Point3D& Point3D::operator/=(const Point3D &v){
    e[0]  /= v.e[0];
    e[1]  /= v.e[1];
    e[2]  /= v.e[2];
    return *this;
}

inline Point3D& Point3D::operator-=(const Point3D& v) {
    e[0]  -= v.e[0];
    e[1]  -= v.e[1];
    e[2]  -= v.e[2];
    return *this;
}

inline Point3D& Point3D::operator*=(const float t) {
    e[0]  *= t;
    e[1]  *= t;
    e[2]  *= t;
    return *this;
}

inline Point3D& Point3D::operator/=(const float t) {
    float k = 1.0/t;
    
    e[0]  *= k;
    e[1]  *= k;
    e[2]  *= k;
    return *this;
}

inline Point3D unit_vector(Point3D v) {
    return v / v.length();
}
