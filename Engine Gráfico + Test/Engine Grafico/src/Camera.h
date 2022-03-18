#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Export.h"
#include "Entity.h"
#include "Window.h"
#include "renderer.h"

class ENGINE_API Camera : public Entity{
public:
	Camera(Renderer* render);
	~Camera();
 
	Window cameraWindow;
	//cameraRenderer;
	glm::mat4 proj;
	glm::mat4 view;

	unsigned int projIndex;
	unsigned int viewIndex;

	void setWindow(Window myWindow);
	     
	Window getWindow();
};

#endif // !CAMERA_H

