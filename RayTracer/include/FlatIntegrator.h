#ifndef _FLATINTEGRATOR_H_
#define _FLATINTEGRATOR_H_

#include "Integrator.h"

class FlatIntegrator : public Integrator {
    public:
        FlatIntegrator(){};
        ~FlatIntegrator();
        void render(const Scene* scene, Sampler* sampler);
        void preprocess( const Scene* scene ) = 0;
        Color Li(Ray& ray, const Scene* scene, Sampler* sampler ) const;
};

#endif