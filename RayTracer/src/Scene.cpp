#include "Scene.h"

Scene::Scene(std::vector<Primitive*> aggregate){
    this->aggregate = aggregate;
}

/// Determines the intersection info; return true if there is an intersection.
bool Scene::intersect(Ray& r, SurfaceInteraction * isect ) const {
    for(Primitive* p : aggregate) {
        if(p->intersect(r, isect)){
            return true;
        }
    }

    return false;
}

bool Scene::intersect_p(Ray& r ) const {
    for(Primitive* p : aggregate) {
        if(p->intersect_p(r)){
            return true;
        }
    }

    return false;
}