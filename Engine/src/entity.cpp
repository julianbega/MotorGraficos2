#include "entity.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/scalar_constants.hpp"
#include "dataManager.h"

int Entity::_nextEntityID = 0;

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

	_id = _nextEntityID++; // assign id and then increase the value so the next entity doesn�t share the same one
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
	
	model.rotation.x = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
	updateModel();
}

void Entity::SetYRot(float angle) {
	transform.rotation[1] = angle;
	glm::vec3 axis;
	axis[0] = 0;
	axis[1] = 1.0f;
	axis[2] = 0;

	model.rotation.y = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
	updateModel();
}

void Entity::SetZRot(float angle) {
	transform.rotation[2] = angle;
	glm::vec3 axis;
	axis[0] = 0;
	axis[1] = 0;
	axis[2] = 1.0f;

	model.rotation.z = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
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
	_id = id;
}

int Entity::GetID() {
	return _id;
}

void Entity::SetName(std::string name) {
	_name = name;
}

void Entity::setEntityColor(glm::vec3 color)
{
	setColor(color);
}

void Entity::setColor(glm::vec3 color)
{
}

void Entity::setColor(float r, float g, float b)
{
}

void Entity::updateForward()
{
	transform.forward.x = glm::cos(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x));
	transform.forward.y = glm::sin(glm::radians(transform.rotation.x));
	transform.forward.z = glm::sin(glm::radians(transform.rotation.y)) * glm::cos(glm::radians(transform.rotation.x));
	transform.forward = glm::normalize(transform.forward);
}

void Entity::updateUp()
{
	transform.up = glm::normalize(glm::cross(transform.right, transform.forward));
}

void Entity::updateRight()
{
	transform.right = glm::normalize(glm::cross(transform.forward, glm::vec3(0, 1, 0)));
}

void Entity::updateVectors()
{
	updateForward();
	updateRight();
	updateUp();
}

std::string Entity::GetName() {
	return _name;
}
