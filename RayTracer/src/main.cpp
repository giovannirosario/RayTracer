#include "SceneBuilder.h"

int main (int argc, char* argv[]) {
    if (argc == 3) {
        SceneBuilder scene_builder;
        scene_builder.run(argv[1], argv[2]);
    }
}