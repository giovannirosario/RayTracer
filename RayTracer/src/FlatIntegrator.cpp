#include "FlatIntegrator.h"
#include "Camera.h"
#include "Buffer.h"
#include "FlatMaterial.h"
#include "SurfaceInteraction.h"
#include <iostream>

FlatIntegrator::FlatIntegrator(){};
FlatIntegrator::~FlatIntegrator(){};

void FlatIntegrator::render(const Scene* scene, Sampler* sampler) {
    // Always call the preprocess() before doing any rendering.
    // This might be just an empty method, or not, depending on the integrator's needs.
    preprocess(scene);

    // This might just be a tile (part) of an image, rendered in parallel.
    int width = camera->film.get_width();
    int height = camera->film.get_height();

    for ( int y = 0 ; y < height ; y++ ) {
        for( int x = 0 ; x < width ; x++ ) {
            Ray ray = camera->generate_ray(x,y);
            Color L = Li(ray, scene, sampler, float(x)/float(width),float(y)/float(height)); // Determine the color for the ray.
            camera->film.draw_pixel(x,y,L); // Set color of pixel (x,y) to L.
        }
    }
}

void FlatIntegrator::preprocess( const Scene* scene ){}

Color FlatIntegrator::Li(Ray& ray, const Scene* scene, Sampler* sampler, float x, float y) const {
    Color L = Color(0,0,0); // The radiance
    // Find closest ray intersection or return background radiance.
    SurfaceInteraction isect = SurfaceInteraction(); 

    if (!scene->intersect(ray, &isect)) {
        //L = scene->background->sample(ray);
        L = scene->background->get_pixel(x, y);
    }
    else {
        const Material *fm = isect.primitive->get_material();
        if (fm != NULL) {
            //Assign diffuse color to L.
            if (fm->type == "flat"){ //Call a method only for FlatMaterial.
                L = fm->color;
            }
        }
    }
    
    return L;
}