#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include "SceneBuilder.h"
#include "FloodFill.h"
#include "Color.h"
#include "Line.h"
#include "Exporter.h"
#include "Canvas.h"
#include "Circle.h"
#include "CircleArc.h"
#include "Polygon.h"
#include "Polyline.h"
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

    Color bg_color;
    int width, height;
    bool anti_aliasing;

    if (scene_json.HasMember("width")) {
        width = scene_json["width"].GetInt();
    }

    if (scene_json.HasMember("height")) {
        height = scene_json["height"].GetInt();
    }

    if (scene_json.HasMember("background_color")) {
        bg_color = parse_color(scene_json["background_color"].GetString());
    }

    if (scene_json.HasMember("anti_aliasing")) {
        anti_aliasing = scene_json["anti_aliasing"].GetBool();
    }

    if(scene_json.HasMember("pallete")) {
        build_pallete(scene_json);
    }

    if (scene_json.HasMember("objects")) {
       for (auto& obj : scene_json["objects"].GetArray()) {
           if(obj.HasMember("type")) {
               std::string type = obj["type"].GetString();
               if (type == "line") {
                   build_line(obj);
               }
               else if (type == "circle") {
                   build_circle(obj);
               }

               else if (type == "polygon") {
                   build_polygon(obj);
               }

               else if (type == "polyline") {
                   build_polyline(obj);
               }

               else if (type == "circle_arc") {
                   build_circle_arc(obj);
               }
           }
       }
    }

    canvas.set_size(width, height);
    canvas.draw_background(bg_color);
    canvas.set_antiAliasing(anti_aliasing);
}


void SceneBuilder::build_pallete(const rapidjson::Document& _pt) {
    for (auto& m : _pt["pallete"].GetObject()) {
        pallete.insert(std::pair<std::string, std::string> (m.name.GetString(), m.value.GetString()));
    }
}


void SceneBuilder::build_line(const rapidjson::Value& _pt) {
    int x1, y1;
    int x2, y2;
    int thickness = 1;
    Color color;

    if (_pt.HasMember("color")) {
        color = parse_color(_pt["color"].GetString());
    }

    if (_pt.HasMember("start")) {
        const rapidjson::Value& values = _pt["start"];
        x1 = values[0].GetInt();
        y1 = values[1].GetInt();
    }
    
    if (_pt.HasMember("end")) {
        const rapidjson::Value& values = _pt["end"];
        x2 = values[0].GetInt();
        y2 = values[1].GetInt();
    }

    if (_pt.HasMember("thickness")) {
        thickness = _pt["thickness"].GetInt();
    }

    Object * obj = new Line(Point2D(x1,y1), Point2D(x2,y2), color, thickness);
    objects.push_back(obj);
}

void SceneBuilder::build_circle(const rapidjson::Value& _pt) {
    int x1, y1;
    int radius;
    int thickness = 1;
    bool fill = false;
    Color stroke_color;
    Color fill_color;
    Object * obj;


    if (_pt.HasMember("stroke_color")) {
        stroke_color = parse_color(_pt["stroke_color"].GetString());
    }

    if (_pt.HasMember("fill_color")) {
        fill_color = parse_color(_pt["fill_color"].GetString());
        fill = true;
    }

    if (_pt.HasMember("start")) {
        const rapidjson::Value& values = _pt["start"];
        x1 = values[0].GetInt();
        y1 = values[1].GetInt();
    }
    
    if (_pt.HasMember("radius")) {
       radius = _pt["radius"].GetInt();
    }
    
    if (_pt.HasMember("thickness")) {
        thickness = _pt["thickness"].GetInt();
    }

    if (fill) {
        obj = new Circle(Point2D(x1,y1), radius, stroke_color, fill_color);
    } else {
        obj = new Circle(Point2D(x1,y1), radius, stroke_color);
    }

    objects.push_back(obj);
}

void SceneBuilder::build_polygon(const rapidjson::Value& _pt) {
    Color stroke_color;
    Color fill_color;
    int thickness = 1;
    std::vector <Point2D> points;
    bool fill = false;
    Object * obj;

    if (_pt.HasMember("stroke_color")) {
        stroke_color = parse_color(_pt["stroke_color"].GetString());
    }

    if (_pt.HasMember("fill_color")) {
        fill_color = parse_color(_pt["fill_color"].GetString());
        fill = true;
    }

    if (_pt.HasMember("points")) {
        const rapidjson::Value& a = _pt["points"];
        for (rapidjson::SizeType i = 0; i < a.Size()-1; i = i+2) {
            Point2D point = Point2D(a[i].GetInt(),a[i+1].GetInt());
            points.push_back(point);
        }
    }

    if (_pt.HasMember("thickness")) {
        thickness = _pt["thickness"].GetInt();
    }

    if (fill) {
        obj = new Polygon(points, stroke_color, fill_color, thickness);
    } else {
        obj = new Polygon(points, stroke_color, thickness);
    }

    objects.push_back(obj);
}

void SceneBuilder::build_polyline(const rapidjson::Value& _pt) {
    Color stroke_color;
    int thickness = 1;
    std::vector <Point2D> points;
    Object * obj;

    if (_pt.HasMember("stroke_color")) {
        stroke_color = parse_color(_pt["stroke_color"].GetString());
    }

    if (_pt.HasMember("points")) {
        const rapidjson::Value& a = _pt["points"];
        for (rapidjson::SizeType i = 0; i < a.Size()-1; i = i+2) {
            Point2D point = Point2D(a[i].GetInt(),a[i+1].GetInt());
            points.push_back(point);
        }
    }

    if (_pt.HasMember("thickness")) {
        thickness = _pt["thickness"].GetInt();
    }

    obj = new Polyline(points, stroke_color, thickness);
    objects.push_back(obj);
}

void SceneBuilder::build_circle_arc(const rapidjson::Value& _pt) {
    int x1, y1;
    int x2, y2;
    int angle;
    int thickness = 1;
    Color stroke_color;

    Object * obj;


    if (_pt.HasMember("stroke_color")) {
        stroke_color = parse_color(_pt["stroke_color"].GetString());
    }

    if (_pt.HasMember("center")) {
        const rapidjson::Value& values = _pt["center"];
        x1 = values[0].GetInt();
        y1 = values[1].GetInt();
    }

    if (_pt.HasMember("start")) {
        const rapidjson::Value& values = _pt["start"];
        x2 = values[0].GetInt();
        y2 = values[1].GetInt();
    }
    
    if (_pt.HasMember("angle")) {
       angle = _pt["angle"].GetInt();
    }
    
    if (_pt.HasMember("thickness")) {
        thickness = _pt["thickness"].GetInt();
    }

    obj = new CircleArc(Point2D(x1,y1), Point2D(x2,y2), angle, stroke_color, thickness);

    objects.push_back(obj);
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