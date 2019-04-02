#include "Exporter.h"

Exporter::Exporter(){}

Exporter::~Exporter() {}

void Exporter::export_png(Buffer color_buffer, std::string f_name) {}

void Exporter::export_ppm(Buffer color_buffer, std::string f_name) {
    std::ofstream file;
    file.open(f_name + ".ppm");
    file << "P3" << std::endl;
    file << color_buffer.get_width() << " " << color_buffer.get_height() << std::endl;
    file << "255 \n";

    Color * pixels = color_buffer.get_canvas();
    
    int h = color_buffer.get_height();
	int w = color_buffer.get_width();

	for ( int j = h-1 ; j >= 0 ; j-- ) {
		for( int i = 0 ; i < w ; i++ ) {
            file << (int) pixels[j * color_buffer.get_width() + i].get_r() << " ";
            file << (int) pixels[j * color_buffer.get_width() + i].get_g() << " ";
            file << (int) pixels[j * color_buffer.get_width() + i].get_b() << " ";
        }
        file << std::endl;
    }
}