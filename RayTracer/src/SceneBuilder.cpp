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
#include "vec3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Sphere.h"
#include "CameraParams.h"
#include "FlatIntegrator.h"
#include "FlatMaterial.h"

SceneBuilder::SceneBuilder() {}

SceneBuilder::~SceneBuilder() {}

void SceneBuilder::read_file(std::string f_name) {
    std::ifstream t(f_name);
    std::stringstream buffer;
    buffer << t.rdbuf();
    scene_string = buffer.str();
}   

void SceneBuilder::write_file(std::string f_name) {
    Exporter exporter;
    exporter.export_ppm(camera->film, f_name);
}

void SceneBuilder::setup() {
    rapidjson::Document scene_json;
    scene_json.Parse(scene_string.c_str());

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

    if (scene_json.HasMember("materials")) {
        build_materials(scene_json);
    }

    if (scene_json.HasMember("objects")) {
        build_objects(scene_json);
    }

    if (scene_json.HasMember("running")) {
        running_setup(scene_json["running"]);
    }
}


void SceneBuilder::running_setup(const rapidjson::Value& _pt) {
    if (_pt.HasMember("integrator")) {
        std::string type;
        int ssp; //samples per pixel
        Color near;
        Color far;

        const rapidjson::Value& _itg = _pt["integrator"];
        if (_itg.HasMember("type")) {
            type = _itg["type"].GetString();
        }
        if (_itg.HasMember("spp")) {
            ssp = _itg["spp"].GetInt();
        }

        if (type == "flat") {
            integrator = new FlatIntegrator();
        }

        if (type == "depth_map") {
           if (_itg.HasMember("near_color")) {
                near = parse_color(_itg["near_color"].GetString());
            }

            if (_itg.HasMember("far_color")) {
                far = parse_color(_itg["far_color"].GetString());
            }

            //integrator = new DepthIntegrator();
        }

        if (type == "normal_map") {
           if (_itg.HasMember("near_color")) {
                near = parse_color(_itg["near_color"].GetString());
            }

            if (_itg.HasMember("far_color")) {
                far = parse_color(_itg["far_color"].GetString());
            }

            //integrator = new NormalMap();
        }
    }
}

void SceneBuilder::build_background(const rapidjson::Value& _pt) {    
    if (_pt.HasMember("type")) {
        std::string type;
        type = _pt["type"].GetString();
        scene->background->set_type(type);
    }
    
    if (_pt.HasMember("colors")) {
        const rapidjson::Value& colors = _pt["colors"];
        for (rapidjson::SizeType i = 0; i < colors.Size(); i++) {
            Color color = parse_color(colors[i].GetString());
            scene->background->add_color(color);
        }
    }
}


void SceneBuilder::build_camera(const rapidjson::Value& _pt) {
    CameraParams cameraParams;

    if (_pt.HasMember("type")) {
        std::string type = _pt["type"].GetString();
        if(type == "orthographic") {
            camera = new OrthoCamera();
        } else if (type == "perspective") {
            camera = new PerspectiveCamera();
        }
    }

    if (_pt.HasMember("width")) {
        cameraParams.width = _pt["width"].GetInt();
    }

    if (_pt.HasMember("width")) {
        cameraParams.height = _pt["height"].GetInt();
    }

    if (_pt.HasMember("position")) {
        const rapidjson::Value& a = _pt["position"];
        cameraParams.position = vec3(a[0].GetInt(),a[1].GetInt(),a[2].GetInt());
    }

    if (_pt.HasMember("target")) {
        const rapidjson::Value& a = _pt["target"];
        cameraParams.target = vec3(a[0].GetInt(),a[1].GetInt(),a[2].GetInt());
    }

    if (_pt.HasMember("up")) {
        const rapidjson::Value& a = _pt["up"];
        cameraParams.up = vec3(a[0].GetInt(),a[1].GetInt(),a[2].GetInt());
    }

    if (_pt.HasMember("vpdim")) {
       const rapidjson::Value& a = _pt["vpdim"];
        cameraParams.vpdim[0] = a[0].GetFloat();
        cameraParams.vpdim[1] = a[1].GetFloat();
        cameraParams.vpdim[2] = a[2].GetFloat();
        cameraParams.vpdim[3] = a[3].GetFloat();
    }

    if (_pt.HasMember("fovy")) {
        cameraParams.fovy = _pt["fovy"].GetFloat();
    }

    if (_pt.HasMember("aspect")) {
        cameraParams.aspect = _pt["aspect"].GetFloat();
    }

    if (_pt.HasMember("fdistance")) {
        cameraParams.fdistance = _pt["fdistance"].GetFloat();
    }

    camera->set_params(cameraParams);
}

void SceneBuilder::build_objects(const rapidjson::Document& _pt) {
    for (auto& obj : _pt["objects"].GetArray()) {
        if(obj.HasMember("type")) {
            std::string type = obj["type"].GetString();
        
            if (type == "sphere") {
                build_sphere(obj);
            }
        }
    }
}


void SceneBuilder::build_materials(const rapidjson::Document& _pt) {
    for (auto& obj : _pt["materials"].GetArray()) {
        std::string type;
        std::string name;
        Color color;
        std::string color_type;
        Material material;

        if(obj.HasMember("type")) {
            type = obj["type"].GetString();
      
            if(obj.HasMember("name")) {
                name = obj["name"].GetString();
            }
            if(obj.HasMember("color")) {
                color = parse_color(obj["color"].GetString());
            }
            if(obj.HasMember("color_type")) {
                color_type = obj["color_type"].GetString();
            }

            if (type == "flat") {
                Material m = FlatMaterial(name, type, color, color_type);
                materials.insert(std::pair<std::string, Material> (name, m));
            }
        }
    }
}

void SceneBuilder::build_sphere(const rapidjson::Value& obj) {
        PrimitiveParams params;
        Material * material;

        if(obj.HasMember("name")) {
            params.name = obj["name"].GetString();
        }

        if(obj.HasMember("type")) {
            params.type = obj["type"].GetString();
        }

        if(obj.HasMember("radius")) {
           params.radius = obj["radius"].GetFloat();
        }

        if (obj.HasMember("center")) {
            const rapidjson::Value& a = obj["center"];
            params.center = vec3(a[0].GetFloat(),a[1].GetFloat(),a[2].GetFloat());
        }

        if (obj.HasMember("material")) {
            std::string m_name = obj["material"].GetString();
           if (materials.count(m_name) > 0) {
               material = &materials.at(m_name);
           }
        }

        Sphere* a = new Sphere(params);
        a->set_material(material);
        primitives.push_back(a);
}


void SceneBuilder::build_pallete(const rapidjson::Document& _pt) {
    for (auto& m : _pt["pallete"].GetObject()) {
        pallete.insert(std::pair<std::string, std::string> (m.name.GetString(), m.value.GetString()));
    }
}

void SceneBuilder::trace() {
    Sampler* sampler;
    integrator->render(scene, sampler);
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
    setup();
    trace();
    write_file(f_out);
}