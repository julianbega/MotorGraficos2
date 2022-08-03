#ifndef CAMERA_H
#define CAMERA_H
#include "export.h"
#include "entity.h"
#include "glm.hpp"

enum class ENGINE_API ProjectionType{
	orthographic, perspective
};
enum class ENGINE_API CameraType {
	free, first, third
};
class ENGINE_API Camera : public Entity {
	ProjectionType _type;

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
	Transform* playerTarget;

public: 
	float rotationSpeed = 10;
	float movementSpeed = 0;

	Camera(class Window* window, Renderer* renderer,ProjectionType type);
	Camera(Window* window, Renderer* renderer, ProjectionType type, CameraType cameraType);
	~Camera();
	void updateView();
	void setProjection(ProjectionType type);
	void init(Shader& shader);
	glm::mat4 getView();
	glm::mat4 getProjection();
	ProjectionType getProjectionType();
	void draw(Shader& shader);
	void setDirection(glm::vec3 target);
	void setTarget(Transform* player);
	void setOffset(float Xoffset, float Yoffset, float Zoffset);
	glm::vec3 getForward();
	glm::vec3 getUp();
	glm::vec3 getRight();
	void rotatePitch(float pitch);
	void rotateYaw(float yaw);
	glm::vec3 camOffset;
	CameraType camType;
private:
	void updateShader(Shader& shader);
	void updateVectors();

	// Inherited via Entity
	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);
};

#endif // !CAMERA_H

