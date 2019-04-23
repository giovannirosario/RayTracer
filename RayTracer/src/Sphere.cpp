#include "Sphere.h"

Sphere::Sphere() {}

Sphere::Sphere(std::string name, std::string type, float radius, vec3 center){
    this->name = name;
    this->type = type;
    this->radius = radius;
    this->center = center;
}

Sphere::~Sphere(){}

bool Sphere::intersect( const Ray& r, SurfaceInteraction * si)  {

}

bool Sphere::intersect_p( const Ray& r ) {

}