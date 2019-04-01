#include "Exporter.h"

Exporter::Exporter(){}

Exporter::~Exporter() {}

void Exporter::export_png(Canvas canvas, std::string f_name) {}

void Exporter::export_ppm(Canvas canvas, std::string f_name) {
    std::ofstream file;
    file.open(f_name + ".ppm");
    file << "P3" << std::endl;
    file << canvas.get_width() << " " << canvas.get_height() << std::endl;
    file << "255 \n";

    Color * pixels = canvas.get_canvas();
    
    for(unsigned int i = 0; i < canvas.get_height(); i++) {
        for(unsigned int j = 0; j < canvas.get_width();j++) {
            file << (int) pixels[i * canvas.get_width() + j].get_r() << " ";
            file << (int) pixels[i * canvas.get_width() + j].get_g() << " ";
            file << (int) pixels[i * canvas.get_width() + j].get_b() << " ";
        }
        file << std::endl;
    }
}