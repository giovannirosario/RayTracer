#ifndef _PARAMSUTIL_H_
#define _PARAMSUTIL_H_

#include <string>

using namespace std;

class ParamsUtil {
    public:
    string PALLETE = "pallete";

    string BACKGROUND = "background";
    string BACKGROUND_TYPE = "type";
    string BACKGROUND_COLORS = "colors";

    string CAMERA = "camera";
    string CAMERA_TYPE = "type";
    string CAMERA_POSITION = "position";
    string CAMERA_TARGET = "target";
    string CAMERA_UP = "up";
    string CAMERA_FOVY = "fovy";
    string CAMERA_ASPECT = "aspect";
    string CAMERA_FDISTANCE = "fdistance";
    string CAMERA_WIDTH = "width";
    string CAMERA_HEIGHT = "height";

    string OBJECTS = "objects";
    string OBJECT_NAME = "name";
    string OBJECET_TYPE = "type";
    string OBJECT_RADIUS = "radius";
    string OBJECT_CENTER = "center";
};

#endif