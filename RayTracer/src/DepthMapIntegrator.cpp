#include "DepthMapIntegrator.h"
#include "Camera.h"
#include "Buffer.h"
#include "FlatMaterial.h"
#include "SurfaceInteraction.h"
#include <iostream>

DepthMapIntegrator::DepthMapIntegrator(){};
DepthMapIntegrator::~DepthMapIntegrator(){};

void DepthMapIntegrator::render(const Scene* scene, Sampler* sampler) {
    // Always call the preprocess() before doing any rendering.
    // This might be just an empty method, or not, depending on the integrator's needs.
    preprocess(scene);

    // This might just be a tile (part) of an image, rendered in parallel.
    int width = camera->film.get_width();
    int height = camera->film.get_height();

    for ( int y = 0 ; y < height ; y++ ) {
        for( int x = 0 ; x < width ; x++ ) {
            Ray ray = camera->generate_ray(x,y);
            //std::cout << x << "," << y << "  " << ray.get_origin() << "__" << ray.get_vDirection() << std::endl;

            Color L = Li(ray, scene, sampler, float(x)/float(width),float(y)/float(height)); // Determine the color for the ray.
            camera->film.draw_pixel(x,y,L); // Set color of pixel (x,y) to L.
        }
    }
}

void DepthMapIntegrator::preprocess( const Scene* scene ){}

Color DepthMapIntegrator::Li(Ray& ray, const Scene* scene, Sampler* sampler, float x, float y) const {
    /* Color L = Color(0,0,0); // The radiance
    // Find closest ray intersection or return background radiance.
    SurfaceInteraction isect = SurfaceInteraction();

    if (!scene->intersect(ray, &isect)) {
        //L = scene->background->sample(ray);
        L = scene->background->get_pixel(x, y);
    }
    else {
         //interpolation
        float delta = (isect.t - zMin) / (zMax - zMin);
        int r = near_color.r() + (far_color.r() - near_color.r()) * delta;
        int g = near_color.g() + (far_color.g() - near_color.g()) * delta;
        int b = near_color.b() + (far_color.b() - near_color.b()) * delta;

        L = Color(r, g, b);
    }

    return L;
    */
}