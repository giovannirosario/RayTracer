#ifndef _SCENE_BUILDER_H_
#define _SCENE_BUILDER_H_

#include <iostream>
#include "rapidjson/document.h"
#include "Buffer.h"
#include "Color.h"
#include "Exporter.h"
#include "vec3.h"
#include "Camera.h"
#include "Background.h"
#include <vector>
#include <string>
#include <map>
#include "Primitive.h"
#include "Scene.h"
#include "Integrator.h"

class SceneBuilder {
    private:
        Scene* scene;
        Camera* camera;
        Integrator* integrator;

        std::string scene_string;
        std::map <std::string, std::string> pallete;
        std::map <std::string, Material> materials;

        std::vector<Primitive*> primitives;
        
    public:
        SceneBuilder();
        ~SceneBuilder();
        void read_file(std::string f_name);
        void write_file(std::string f_name);
        void setup();
        void running_setup(const rapidjson::Value& _pt);
        void build_pallete(const rapidjson::Document& _pt);
        void build_background(const rapidjson::Value& _pt);
        void build_camera(const rapidjson::Value& _pt);
        void build_objects(const rapidjson::Document& _pt);
        void build_materials(const rapidjson::Document& _pt);
        void build_sphere(const rapidjson::Value& obj);
        Color parse_color(const char * hex_string); 
        void run(std::string f_in, std::string f_out);
        void trace();
};

#endif