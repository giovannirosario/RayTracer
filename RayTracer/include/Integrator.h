#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Sampler.h"
#include "Scene.h"

class Integrator {
    protected:
        Camera* camera;
        Sampler* sampler;

    public:
        Integrator(){};
        virtual ~Integrator(){};
        virtual void render(const Scene* scene, Sampler* sampler) =0;
        virtual void preprocess( const Scene* scene ) = 0;
        virtual Color Li(Ray& ray, const Scene* scene, Sampler* sampler, float x, float y) const = 0;
};
#endif