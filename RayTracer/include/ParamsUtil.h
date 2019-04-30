#ifndef _PARAMSUTIL_H_
#define _PARAMSUTIL_H_

#include <string>

using namespace std;

class ParamsUtil {
    public:
    const string PALLETE = "pallete";

    const string BACKGROUND = "background";
    const string BACKGROUND_TYPE = "type";
    const string BACKGROUND_COLORS = "colors";

    const string CAMERA = "camera";
    const string CAMERA_TYPE = "type";
    const string CAMERA_POSITION = "position";
    const string CAMERA_TARGET = "target";
    const string CAMERA_UP = "up";
    const string CAMERA_FOVY = "fovy";
    const string CAMERA_ASPECT = "aspect";
    const string CAMERA_FDISTANCE = "fdistance";
    const string CAMERA_WIDTH = "width";
    const string CAMERA_HEIGHT = "height";

    const string OBJECTS = "objects";
    const string OBJECT_NAME = "name";
    const string OBJECET_TYPE = "type";
    const string OBJECT_RADIUS = "radius";
    const string OBJECT_CENTER = "center";
};

#endif