#ifndef _FLATINTEGRATOR_H_
#define _FLATINTEGRATOR_H_

#include "Integrator.h"

class FlatIntegrator : public Integrator {
    public:
        FlatIntegrator();
        ~FlatIntegrator();
        void render(const Scene* scene, Sampler* sampler);
        void preprocess( const Scene* scene );
        Color Li(Ray& ray, const Scene* scene, Sampler* sampler, float x, float y) const;
};

#endif