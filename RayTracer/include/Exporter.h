#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <fstream>
#include <iostream>
#include "Canvas.h"

class Exporter {
    public:
        Exporter();
        ~Exporter();
        void export_png(Canvas canvas, std::string f_name);
        void export_ppm(Canvas canvas, std::string f_name);
};

#endif