#ifndef CAMERA_H
#define CAMERA_H
#include "export.h"
#include "entity.h"
#include "input.h"
#include "time_manager.h"
#include "glm.hpp"

enum class ENGINE_API ProjectionType{
	orthographic, perspective
};
enum class ENGINE_API CameraType {
	free, firstPerson, thirdPerson
};
class ENGINE_API Camera : public Entity {
	ProjectionType _type;
	CameraType _camTytpe;
	glm::mat4 _view;
	glm::mat4 _proj;
	glm::vec3 _right;
	glm::vec3 _up;
	glm::vec3 _worldUp;
	glm::vec3 _forward;
	glm::vec3 _inverseDirection;

	class Window* _window;

	float pitch;
	float yaw;

public: 
	float rotationSpeed = 10;
	float movementSpeed = 1;
	float speed = 1;
	Camera(class Window* window, Renderer* renderer,ProjectionType type, CameraType camTytpe);
	~Camera();
	void updateView();
	void setProjection(ProjectionType type);
	void init(Shader& shader);
	glm::mat4 getView();
	glm::mat4 getProjection();
	ProjectionType getProjectionType();
	void draw(Shader& shader);
	void setDirection(glm::vec3 target);
	glm::vec3 getForward();
	glm::vec3 getUp();
	glm::vec3 getRight();
	void rotatePitch(float pitch);
	void rotateYaw(float yaw);
	void inputs(Input input, Time time);
private:
	void updateShader(Shader& shader);
	void updateVectors();
};

#endif // !CAMERA_H

