__COMPUTER GRAPHICS I (DIM0451) -- 2019.1 --  Ray Tracer Project__

# Project 1 - Basic Infrastructure

## Requirements

Implemented:
1. A class `Buffer` (the `Canvas` class from the previous assignment)  that handles pixels values as an **image color buffer**. This allows the ray tracer to save the color buffer to an image file in PPM or PNG format.
2. A class `Background` that is responsible for returning a color each time the primary ray misses any object in the scene (i.e. hits nothing).
3. A set of classes to handle the math operations on vectors and matrices.
4. The _main loop_ of the  ray tracing algorithm, which should traverse the image pixels and shoot rays into the scene. At this stage, the main loop only traverses the image and samples colors from the `Background` object. (no rays are shot just yet)
5. A parser class or set of functions that reads in a scene description file in JSON with the format explained below.

## The Scene Format

Here is an example scene file:
```json
{
    "pallete": {
        "blue":"0000FF",
        "cyan":"00FFFF",
    },
    "background":{
        "type":"interpolation",
        "colors":["000033","00FF33","FFFF33", "FF0033"]
    },
    "camera": {
        "type":"orthographic",
        "width":600,
        "height":400
    }
}
```
All elements are declared inside a JSON document. At this stage, we only have two inner JSON Objects, `background` and `camera`.

Background supports "interpolation" (up to 4 colors) and "solid" (1 color) types.

This scene would generate the image below:
<!--  ![background_result](pics/saida.png =400x) -->
 <img src="/RayTracer/scene.ppm" width="350">


## Upcoming projects - Version Control
As we progress through the upcoming projects, each new project will be place in a different branch in git.The master branch will always contain the currently version i am working on. Branch "P-01" contains "Project 1 - Basic Infrastructure", "P-02" will contain Project 02 and so goes on for each of the individual steps throughout the semester. This, will keep an easy-to-access evolution timeline of my  ray tracing project over the semester.
