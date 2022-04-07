#ifndef ENTITY_H
#define ENTITY_H
#include "export.h"
#include "renderer.h"
#include "mat4x4.hpp"

// using glm vec3 temporarily, will later use my
struct ENGINE_API Rotation {
	glm::mat4 x;
	glm::mat4 y;
	glm::mat4 z;
};

struct ENGINE_API Model {
	glm::mat4 translate;
	Rotation rotation;
	glm::mat4 scale;
	glm::mat4 trs;
};

struct ENGINE_API Transform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

//basic enitity for now
class ENGINE_API Entity {
protected:
	int _id;
	static int _nextEntityID;
	std::string _name = "";
	Renderer* _renderer;
	Model model;

	void updateModel();
	void updateMatrices();
public:
	Entity(Renderer* renderer);
	~Entity();
	Transform transform;
	Renderer* GetRenderer();
	glm::mat4 GetModel();
	void SetPosition(float x, float y, float z);
	void SetXRot(float angle);
	void SetYRot(float angle);
	void SetZRot(float angle);
	void SetScale(float x, float y, float z);
	void SetID(int id);
	int GetID();
	void SetName(std::string name);
	std::string GetName();
	void updateVectors(glm::vec3 worldUp);
	glm::vec3 getForward();
	glm::vec3 getUp();
	glm::vec3 getRight();
	glm::vec3 _forward;
	glm::vec3 _right;
	glm::vec3 _up;
};

#endif // !ENTITY_H

