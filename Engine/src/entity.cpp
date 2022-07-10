#include "entity.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/scalar_constants.hpp"
#include "dataManager.h"

int Entity::nextEntityID = 0;

void Entity::updateModel() {
	model.trs = model.translate * model.rotation.x * model.rotation.y * model.rotation.z * model.scale;
}

Entity::Entity(Renderer* renderer) {

	_renderer = renderer;
	model.translate = glm::mat4(1.0);

	model.rotation.x = glm::mat4(1.0);
	model.rotation.y = glm::mat4(1.0);
	model.rotation.z = glm::mat4(1.0);
	model.scale = glm::mat4(1.0);

	SetScale(1.0f, 1.0f, 1.0f);
	SetPosition(0.0f, 0.0f, 0.0f);
	SetXRot(0.0f);
	SetYRot(0.0f);
	SetZRot(0.0f);

	id = nextEntityID++; // assign id and then increase the value so the next entity doesn´t share the same one

	forward = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(1, 0, 0);

}

Entity::~Entity() {
}

Renderer* Entity::GetRenderer() {
	return _renderer;
}

glm::mat4 Entity::GetModel() {
	return model.trs;
}

void Entity::SetPosition(float x, float y, float z) {
	transform.position.x = x;
	transform.position.y = y;
	transform.position.z = z;
	
	model.translate = glm::translate(glm::mat4(1.0f), transform.position);
	updateModel();
}

void Entity::updateMatrices(){
	model.translate = glm::translate(glm::mat4(1.0f), transform.position);
	model.scale = glm::scale(glm::mat4(1.0f), transform.scale);

	updateModel();
}

void Entity::SetXRot(float angle) {
	transform.rotation[0] = angle;
	glm::vec3 axis;
	axis[0] = 1.0f;
	axis[1] = 0;
	axis[2] = 0;
	
	model.rotation.x = glm::rotate(glm::mat4(1.0f), angle, axis);
	updateModel();
}

void Entity::SetYRot(float angle) {
	transform.rotation[1] = angle;
	glm::vec3 axis;
	axis[0] = 0;
	axis[1] = 1.0f;
	axis[2] = 0;

	model.rotation.y = glm::rotate(glm::mat4(1.0f), angle, axis);
	updateModel();
}

void Entity::SetZRot(float angle) {
	transform.rotation[2] = angle;
	glm::vec3 axis;
	axis[0] = 0;
	axis[1] = 0;
	axis[2] = 1.0f;

	model.rotation.z = glm::rotate(glm::mat4(1.0f), angle, axis);
	updateModel();
}

void Entity::SetScale(float x, float y, float z) {
	transform.scale.x = x;
	transform.scale.y = y;
	transform.scale.z = z;

	model.scale = glm::scale(glm::mat4(1.0f), transform.scale);
	updateModel();
}

void Entity::SetID(int id) {
	id = id;
}

int Entity::GetID() {
	return id;
}

void Entity::SetName(std::string entityName) {
	name = entityName;
}

std::string Entity::GetName() {
	return name;
}

void Entity::updateVectors(glm::vec3 worldUp)
{
	this->forward.x = glm::cos(glm::radians(this->transform.rotation.y)) * glm::cos(glm::radians(this->transform.rotation.x));
	this->forward.y = glm::sin(glm::radians(this->transform.rotation.x));
	this->forward.z = glm::sin(glm::radians(this->transform.rotation.y)) * glm::cos(glm::radians(this->transform.rotation.x));
	this->forward = glm::normalize(this->forward);
	this->right = glm::normalize(glm::cross(this->forward, worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->forward));

	//limita rotacion de pitch
	if (this->transform.rotation.x >= 89.9f) this->transform.rotation.x = 89.9f;
	if (this->transform.rotation.x <= -89.9f) this->transform.rotation.x = -89.9f;
}


glm::vec3 Entity::getForward() {
	return forward;
}
glm::vec3 Entity::getUp() {
	return up;
}
glm::vec3 Entity::getRight() {
	return right;
}