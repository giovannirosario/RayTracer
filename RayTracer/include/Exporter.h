#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <fstream>
#include <iostream>
#include "Buffer.h"

class Exporter {
    public:
        Exporter();
        ~Exporter();
        void export_png(Buffer color_buffer, std::string f_name);
        void export_ppm(Buffer color_buffer, std::string f_name);
};

#endif