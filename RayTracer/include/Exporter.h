#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <fstream>
#include <iostream>
#include "Buffer.h"

class Exporter {
    public:
        Exporter();
        ~Exporter();
        void export_png(Buffer canvas, std::string f_name);
        void export_ppm(Buffer canvas, std::string f_name);
};

#endif