#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include "SceneBuilder.h"
#include "Color.h"
#include "Exporter.h"
#include "Buffer.h"
#include <iostream>
#include <fstream>
#include <sstream>

SceneBuilder::SceneBuilder() {}

SceneBuilder::~SceneBuilder() {}

void SceneBuilder::read_file(std::string f_name) {
    std::ifstream t(f_name);
    std::stringstream buffer;
    buffer << t.rdbuf();
    scene = buffer.str();
}

void SceneBuilder::write_file(std::string f_name) {
    Exporter exporter;
    exporter.export_ppm(canvas, f_name);
}

void SceneBuilder::build_scene() {
    rapidjson::Document scene_json;
    scene_json.Parse(scene.c_str());

    int width, height;

    if(scene_json.HasMember("pallete")) {
        build_pallete(scene_json);
    }

    if (scene_json.HasMember("background")) {
        build_background(scene_json["background"]);
    }

    if (scene_json.HasMember("camera")) {
        build_camera(scene_json["camera"]);
    }
}


void SceneBuilder::build_background(const rapidjson::Value& _pt) {    
    if (_pt.HasMember("type")) {
        std::string type;
        type = _pt["type"].GetString();
        background.set_type(type);
    }
    
    if (_pt.HasMember("colors")) {
        const rapidjson::Value& colors = _pt["colors"];
        for (rapidjson::SizeType i = 0; i < colors.Size(); i++) {
            Color color = parse_color(colors[i].GetString());
            background.add_color(color);
        }
    }
}


void SceneBuilder::build_camera(const rapidjson::Value& _pt) {    
    int width, height;
    if (_pt.HasMember("type")) {
        std::string type;
        type = _pt["type"].GetString();
        camera.set_type(type);
    }
    if (_pt.HasMember("width")) {
        width = _pt["width"].GetInt();
    }
    if (_pt.HasMember("height")) {
        height = _pt["height"].GetInt();
    }

    camera.set_size(width, height);    
}

void SceneBuilder::build_pallete(const rapidjson::Document& _pt) {
    for (auto& m : _pt["pallete"].GetObject()) {
        pallete.insert(std::pair<std::string, std::string> (m.name.GetString(), m.value.GetString()));
    }
}

void SceneBuilder::draw_scene() {
    for (unsigned int i = 0; i < objects.size(); i++) {
        objects[i]->draw(canvas);
    }
}

Color SceneBuilder::parse_color(const char * hex_string) {
    std::string aux = hex_string;

    if (pallete.count(aux) > 0) {
        aux = pallete.at(aux);
    }

    const char *aux_c = aux.c_str();

    int r, g, b;
    sscanf(aux_c, "%02x%02x%02x", &r, &g, &b);
    Color c = Color(r,g,b);
    return c;
}

void SceneBuilder::flood_fill(){
    rapidjson::Document scene_json;
    scene_json.Parse(scene.c_str());

    Color color;
    int x,y;

    if (scene_json.HasMember("flood_fill")) {
       for (auto& obj : scene_json["flood_fill"].GetArray()) {
           if (obj.HasMember("color")) {
                color = parse_color(obj["color"].GetString());
            }

            if (obj.HasMember("start")) {
                const rapidjson::Value& values = obj["start"];
                x = values[0].GetInt();
                y = values[1].GetInt();
            }
            
            FloodFill(canvas,x,y,color);
       }
    }

}


void SceneBuilder::raster(std::string f_in, std::string f_out) {
    read_file(f_in);
    build_scene();
    draw_scene();
    flood_fill();
    write_file(f_out);
}