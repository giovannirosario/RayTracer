#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include "Ray.h"
#include "Primitive.h"
#include "Background.h"

class Scene {
    public:
        //std::vector<Light*> lights; // list of lights
        Background* background; // The background object.
    private:
        std::vector<Primitive*> aggregate; // The scene graph of objects, acceleration structure.

    public:
        Scene(std::vector<Primitive*> aggregate){}
        /// Determines the intersection info; return true if there is an intersection.
        bool intersect(Ray& r, SurfaceInteraction *isect ) const;
        /*! A faster version that only determines whether there is an intersection or not;*/
        bool intersect_p(Ray& r ) const;
};

#endif