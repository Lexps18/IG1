#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene1::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	RGBTriangle* tri = new RGBTriangle(200.0); // tamaño 200
	gObjects.push_back(tri);

	gObjects.push_back(new RGBAxes(400.0));
	RegularPolygon* pentagono= new RegularPolygon(5,200.0);//pentagono
	glm::vec4 magenta(255.0, 0.0, 255.0, 1.0);
	pentagono->setColor(magenta);
	gObjects.push_back(pentagono);

	RegularPolygon* circulo = new RegularPolygon(50, 200.0);//circulo
	glm::vec4 amarillo(255.0, 255.0, 0.0, 1.0);
	circulo->setColor(amarillo);
	gObjects.push_back(circulo);
}

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : gObjects)
		delete el;

	gObjects.clear();
}

void
Scene::load()
{
	for (Abs_Entity* obj : gObjects)
		obj->load();
}

void
Scene::unload()
{
	for (Abs_Entity* obj : gObjects)
		obj->unload();
}

void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque) cambiado a azul.
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());
}
