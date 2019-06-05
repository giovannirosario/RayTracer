
#ifndef _DEPTHMAPINTEGRATOR_H_
#define _DEPTHMAPINTEGRATOR_H_

#include "Integrator.h"

class DepthMapIntegrator : public Integrator {
    public:
        DepthMapIntegrator();
        ~DepthMapIntegrator();
        void render(const Scene* scene, Sampler* sampler);
        void preprocess( const Scene* scene );
        Color Li(Ray& ray, const Scene* scene, Sampler* sampler, float x, float y) const;
};

#endif