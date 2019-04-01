__COMPUTER GRAPHICS I (DIM0451) -- 2019.1 --  Ray Tracer Project__

# Project 1 - Basic Infrastructure

In this programming project you will begin writing your own ray tracer.

We've learned from the lessons so far that a basic ray tracing algorithm works by shooting **rays** through **pixels** of an image into a **scene**; every time a ray hits something in the scene, the algorithm triggers some form of **shader** to determine the color of that pixel. By **shader** we mean another class or procedure, **physically based** or otherwise, that might shoot other rays, stop on the first hit (i.e. a _ray casting_), compute the contribution of the **lights** in the scene, for example, to determine and return a _rgb_ color (see figure below, from Chapter 4 of _"Fundamentals of Computer Graphics"_, 3rd ed., Shirley and Marschner).

<img src="./pics/viewraytri.png" width="350">


At this point, several of the ray tracing components mentioned above are to be considered **black boxes**. For now, our major concern is to understand the _"big picture"_ and lay down the foundations of our ray tracing, which, in turn, will be extended and experimented with along the next projects.

## Requirements

We'll start with the basic elements of a ray tracer, namely
1. A class `Buffer` (the `Canvas` class from the previous assignment)  that handles pixels values as an **image color buffer**. This allows the ray tracer to save the color buffer to an image file in PPM or PNG format. The class is named `Buffer` because later on we might want to create other types of buffer, such as the **z buffer**. Sometimes we may need more than one buffer while creating a 3D image.
2. A class `Background` that is responsible for returning a color each time the primary ray misses any object in the scene (i.e. hits nothing).
3. A set of classes to handle the math operations on vectors and matrices. In this case you might either implement your own library (`Vec3`, `Point3`, `Mat3x3`, etc.) based on the one provided in [_"Ray Tracing in One Weekend"_](https://github.com/petershirley/raytracinginoneweekend/releases/), or adopt other math libraries such as [_OpenGL Mathematics_](https://glm.g-truc.net/0.9.9/index.html), or [_cyCodeBase_](http://www.cemyuksel.com/cyCodeBase/code.html).
4. The _main loop_ of the  ray tracing algorithm, which should traverse the image pixels and shoot rays into the scene. At this stage, the main loop only traverses the image and samples colors from the `Background` object. (no rays are shot just yet)
5. A parser class or set of functions that reads in a scene description file (in XML, YAML, JSON, or your own mark up language) with the format explained below.

## The Scene Format

Here we provide a basic XML format for describing the scene, only as a driving example. Feel free to adapt the scene format to your chosen markup language. Upcoming projects will have additional tags that we will define when we need them.

Here is an example scene file:
```xml
<raytracer>
  <background type="solid">
	  <color r="153" g="204" b="255">
  </background>
  <camera type="orthographic">
    <width value="800"/>
    <height value="600"/>
  </camera>
</raytracer>
```
All elements are declared inside a `raytracer` tag. _You might want to replace this tag with you ray tracer program name._ At this stage, we only have two (same level) tags, `background` and `camera`. Later on we will add `scene`, `light`, `material`, etc.

In the example above, we asked for a solid background, which means a single color (in this case, a light blue sky) for the entire background. Another option for this tag would be to choose `type="interpolation"` and define up to 4 colors, which would correspond, respectively, to the bottom-left, top-left, top-right, and bottom-right of the rectangle associated with the background.  The rectangle corners should be provided in _clockwise_ fashion, starting from bottom-left. Notice that the last color provided should be replicated in the other corners if they have been omitted. This allows user to specify one, two, three or four color for the `background` tag. 

The ray tracer should apply [**bilinear interpolation**](https://en.wikipedia.org/wiki/Bilinear_interpolation) when sampling the background. You may want to provide a method with the following prototype:
```c++
rgb Background::sample( float i, float j );
```
where `rgb` means a color in the three-dimensional RBG space, and `i` and `j` are values in $[0;1]$ corresponding to the normalized location of the pixel `(i,j)` in the color buffer. 

Here is another example, this time asking for a background generated through interpolation.

```xml
<raytracer>
  <settings>
	  <output_file type="PNG" name="saida.png">
  </settings>
  <background type="interpolation">
	  <color r="0"   g="0"   b="51"> <!-- bottom left  -->
	  <color r="0"   g="255" b="51"> <!-- top left     -->
	  <color r="255" g="255" b="51"> <!-- top right    -->
	  <color r="255" g="0"   b="51"> <!-- bottom right -->
  </background>
  <camera type="orthographic">
    <width value="200"/>
    <height value="100"/>
  </camera>
</raytracer>
```
This scene would generate the image below:
<!--  ![background_result](pics/saida.png =400x) -->
 <img src="./pics/saida.png" width="350">


Notice that this scene file has a new tag, `settings`, that should set some configuration parameter of the ray tracing program, such as samples per pixel, number of bounces, etc. Some may argue that this settings does not belong in a scene file, since it does not describe any component of a scene per se but, instead, how some of the ray tracing running parameters should be set. If this semantic inconsistency bothers you, you may ignore this tag and set the ray tracing parameters through other means, such a configuration file, for instance.

Next, we provide a simple version of the main loop illustrating a possible usage of (some of) these classes together.
```c++
\\ [1] Parser and load scene file
\\ [2] Instantiate the Camera and Background objects.
\\ [3] Enter the ray tracing main loop
int main() {
	// Perform objects initialization here.
	// ...
	Buffer color_buffer( camera.width(), camera.height() );
	auto w = color_buffer.height();
	auto h = color_buffer.width();
	for ( int j = h-1 ; j >= 0 ; j-- ) {
		for( int i = 0 ; i < w ; i++ ) {
			// Not shooting rays just yet; so let us sample the background.
			auto color = background.sample( float(i)/float(w), float(j)/float(h) ); // get background color.
			color_buffer.pixel( color, i, j ); // set image buffer at position (i,j), accordingly.
		}
	}
	// send image color buffer to the output file.
	save_png_image( "saida.png", color_buffer.data() );
}
```



## Recommendations

Rather than updating (overwriting) the ray tracer program as we progress through the upcoming individual projects, I recommend that you create a separate folder for each new project. I understand that this will cause _code replication_, but the purpose of this recommendation is to make it easy to keep track of the individual steps throughout the semester. This, in turn, will allow me to provide progressive grading for the intermediate steps each time a due project is delivered, while keeping an easy-to-access evolution timeline of your ray tracing project over the semester.
