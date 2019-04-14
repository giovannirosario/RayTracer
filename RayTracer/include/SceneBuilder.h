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

class SceneBuilder {
    private:
        Buffer color_buffer;
        Background background;
        Camera * camera;
        std::string scene;
        std::map <std::string, std::string> pallete;
        
    public:
        SceneBuilder();
        ~SceneBuilder();
        void read_file(std::string f_name);
        void write_file(std::string f_name);
        void build_scene();
        void build_pallete(const rapidjson::Document& _pt);
        void build_background(const rapidjson::Value& _pt);
        void build_camera(const rapidjson::Value& _pt);
        Color parse_color(const char * hex_string); 
        void run(std::string f_in, std::string f_out);
        void trace();
};

#endif