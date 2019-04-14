#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include "SceneBuilder.h"
#include "Color.h"
#include "Exporter.h"
#include "Buffer.h"
#include "OrthoCamera.h"
#include "PerspectiveCamera.h"
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
    exporter.export_ppm(color_buffer, f_name);
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
    if (_pt.HasMember("type")) {
        if(_pt["type"].GetString() == "orthographic") {
            camera = new OrthoCamera();
        } else if (_pt["type"].GetString() == "perspective") {
            camera = new PerspectiveCamera();
        }
    }

    if (_pt.HasMember("width") && _pt.HasMember("height")) {
        camera->set_size(_pt["width"].GetInt(),_pt["height"].GetInt());   
    }

    if (_pt.HasMember("position")) {
        const rapidjson::Value& a = _pt["position"];
            camera->set_position(vec3(a[0].GetInt(),a[1].GetInt(),a[2].GetInt()));
    }

    if (_pt.HasMember("target")) {
        const rapidjson::Value& a = _pt["target"];
            camera->set_target(vec3(a[0].GetInt(),a[1].GetInt(),a[2].GetInt()));
    }

    if (_pt.HasMember("up")) {
        const rapidjson::Value& a = _pt["up"];
            camera->set_up(vec3(a[0].GetInt(),a[1].GetInt(),a[2].GetInt()));
    }


}

void SceneBuilder::build_pallete(const rapidjson::Document& _pt) {
    for (auto& m : _pt["pallete"].GetObject()) {
        pallete.insert(std::pair<std::string, std::string> (m.name.GetString(), m.value.GetString()));
    }
}

void SceneBuilder::trace() {
    color_buffer.set_size(camera->get_width(), camera->get_height());
	int h = color_buffer.get_height();
	int w = color_buffer.get_width();

	for ( int j = h-1 ; j >= 0 ; j-- ) {
		for( int i = 0 ; i < w ; i++ ) {
			Color color = background.get_pixel( float(i)/float(w), float(j)/float(h)); 
			color_buffer.draw_pixel(i,j,color); 
        }
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

void SceneBuilder::run(std::string f_in, std::string f_out) {
    read_file(f_in);
    build_scene();
    trace();
    write_file(f_out);
}