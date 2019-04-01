#ifndef _SCENE_BUILDER_H_
#define _SCENE_BUILDER_H_

#include <iostream>
#include "rapidjson/document.h"
#include "Canvas.h"
#include "Color.h"
#include "Exporter.h"
#include "Point2D.h"
#include "Object.h"
#include <vector>
#include <string>
#include <map>

class SceneBuilder {
    private:
        Canvas canvas;
        std::string scene;
        std::vector<Object*> objects;
        std::map <std::string, std::string> pallete;
        
    public:
        SceneBuilder();
        ~SceneBuilder();
        void read_file(std::string f_name);
        void write_file(std::string f_name);
        void build_scene();
        void build_pallete(const rapidjson::Document& _pt);
        void build_line(const rapidjson::Value& _pt);
        void build_circle(const rapidjson::Value& _pt);
        void build_polygon(const rapidjson::Value& _pt);
        void build_polyline(const rapidjson::Value& _pt);
        void build_circle_arc(const rapidjson::Value& _pt);
        void draw_scene();
        void flood_fill();
        Color parse_color(const char * hex_string);
        void raster(std::string f_in, std::string f_out);
};

#endif