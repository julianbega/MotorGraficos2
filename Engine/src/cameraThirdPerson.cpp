/*#include "cameraThirdPerson.h"

CameraThirdPerson::CameraThirdPerson(Window* window, Renderer* renderer, ProjectionType type)
{
	_window = window;
	_view = glm::mat4(1.0f);
	_proj = glm::mat4(1.0f);
	_name = "Camera";
	_type = type;
	_worldUp = glm::vec3(0, 1, 0);
	_forward = glm::vec3(0, 0, -1);

	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
}

CameraThirdPerson::~CameraThirdPerson()
{
}

void CameraThirdPerson::inputs(Input input, Time time)
{
}
*/