#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "camera.h"
#include "gtc/matrix_transform.hpp"
#include "mat4x4.hpp"
#include "gtc/type_ptr.hpp"
#include "detail/type_mat4x4.hpp"
#include "dataManager.h"
#include "window.h"


Camera::Camera(Window* window, Renderer* renderer, ProjectionType type, CameraType camTytpe) : Entity(renderer) {
	_pivot = new Entity(renderer);
	_window = window;
	_view = glm::mat4(1.0f);
	_proj = glm::mat4(1.0f);
	name = "Camera";
	_type = type;
	_worldUp = glm::vec3(0, 1, 0);	
	_camTytpe = camTytpe;
	DataManager* data = DataManager::Get();
	data->addEntity(this, id);
	_pivot->transform = this->transform;
	
}

Camera::~Camera() {

}

void Camera::updateView() {
	_view = glm::lookAt(transform.position, transform.position +  forward, up);
}

void Camera::setProjection(ProjectionType type) {
	_type = type;
	float windowWidth = static_cast<float>(_window->getWidth());
	float windowHeight = static_cast<float>(_window->getHeight());
	switch (_type)
	{
	case ProjectionType::orthographic:
		_proj = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight, 0.1f, 100.0f);
		break;
	case ProjectionType::perspective:
		// FOV					      Aspect	     near   far
		_proj = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 1.f, 100.0f);
		break;
	default:
		break;
	}

}

void Camera::init(Shader& shader) {
	setProjection(_type);
	updateVectors(_worldUp);
	_pivot->updateVectors(_worldUp);
	updateView();
	updateShader(shader);
	if (_camTytpe == CameraType::thirdPerson)
	{	
		offset = glm::vec3(0, 1, 3);
		this->transform.position += offset;
		setDirection(_pivot->transform.position);
	}
}

glm::mat4 Camera::getView() {
	return _view;
}

glm::mat4 Camera::getProjection() {
	return _proj;
}

ProjectionType Camera::getProjectionType() {
	return _type;
}

void Camera::draw(Shader& shader) {
	updateVectors(_worldUp);
	_pivot->updateVectors(_worldUp);
	updateView();

	_renderer->drawCamera(shader, GetModel(), getView(), getProjection());
}



void Camera::rotatePitch(float pitch){
	transform.rotation.x += pitch;
}

void Camera::rotateYaw(float yaw) {
	transform.rotation.y += yaw;
}

void Camera::inputs(Input input,Time time)
{
	switch (this->_camTytpe)
	{
	case CameraType::free:
	{
		if (input.getKey(keyCode::W)) {
			transform.position += getForward() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::S)) {
			transform.position -= getForward() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::A)) {
			transform.position -= getRight() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::D)) {
			transform.position += getRight() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::RIGHT)) {
			this->rotationSpeed= 100 * time.getDeltaTime();
			this->rotateYaw(this->rotationSpeed);
		}
		if (input.getKey(keyCode::LEFT)) {
			this->rotationSpeed = 100 * time.getDeltaTime();
			this->rotateYaw(-this->rotationSpeed);
		}
		if (input.getKey(keyCode::UP)) {
			this->rotationSpeed = 100 * time.getDeltaTime();
			this->rotatePitch(this->rotationSpeed);
		}
		if (input.getKey(keyCode::DOWN)) {
			this->rotationSpeed = 100 * time.getDeltaTime();
			this->rotatePitch(-this->rotationSpeed);
		}
	}
		break;
	case CameraType::firstPerson:
	{
		if (input.getKey(keyCode::W)) {
			
			_pivot->transform.position -= _pivot->getRight() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::S)) {
			_pivot->transform.position += _pivot->getRight() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::A)) {
			_pivot->transform.position -= _pivot->getForward() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::D)) {
			_pivot->transform.position += _pivot->getForward() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::RIGHT)) {
			this->rotationSpeed = 100 * time.getDeltaTime();
			this->rotateYaw(this->rotationSpeed);
			_pivot->transform.rotation.y += this->rotationSpeed;
		}
		if (input.getKey(keyCode::LEFT)) {
			this->rotationSpeed = 100 * time.getDeltaTime();
			this->rotateYaw(-this->rotationSpeed);
			_pivot->transform.rotation.y += -this->rotationSpeed;
		}
		if (input.getKey(keyCode::UP)) {
			this->rotationSpeed = 100 * time.getDeltaTime();
			this->rotatePitch(this->rotationSpeed);
		}
		if (input.getKey(keyCode::DOWN)) {
			this->rotationSpeed = 100 * time.getDeltaTime();
			this->rotatePitch(-this->rotationSpeed);
		}
		transform.position = _pivot->transform.position;
	}
		break;
	case CameraType::thirdPerson:
	{
		if (input.getKey(keyCode::W)) {

			_pivot->transform.position -= _pivot->getRight() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::S)) {
			_pivot->transform.position += _pivot->getRight() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::A)) {
			_pivot->transform.position -= _pivot->getForward() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::D)) {
			_pivot->transform.position += _pivot->getForward() * (speed * time.getDeltaTime());
		}
		if (input.getKey(keyCode::RIGHT)) {
			this->rotationSpeed = 100 * time.getDeltaTime();
			this->rotateYaw(this->rotationSpeed);
			_pivot->transform.rotation.y += this->rotationSpeed;
		}
		if (input.getKey(keyCode::LEFT)) {
			this->rotationSpeed = 100 * time.getDeltaTime();
			this->rotateYaw(-this->rotationSpeed);
			_pivot->transform.rotation.y += -this->rotationSpeed;
		}

		transform.position = _pivot->transform.position + offset;
	}
		break;
	default:
		break;
	}
	
}



void Camera::updateShader(Shader& shader){
	unsigned int transformLoc = glGetUniformLocation(shader.getID(), "transform");
	unsigned int viewLoc = glGetUniformLocation(shader.getID(), "view");
	unsigned int projLoc = glGetUniformLocation(shader.getID(), "proj");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(GetModel()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(getView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(getProjection()));
}

void Camera::setDirection(glm::vec3 target){
	_inverseDirection = glm::normalize(transform.position - target);
}

Transform Camera::getPivot()
{
	return _pivot->transform;
}
