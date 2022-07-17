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

struct ENGINE_API EntityModel {
	glm::mat4 translate;
	Rotation rotation;
	glm::mat4 scale;
	glm::mat4 trs;
};

struct ENGINE_API Transform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
};

//basic enitity for now
class ENGINE_API Entity {
protected:
	int _id;
	static int _nextEntityID;
	std::string _name = "";
	Renderer* _renderer;
	EntityModel model;
	bool _isLightSource = false;
	Shader _entityShader;

	void updateModel();
	void updateMatrices();
	void updateUp();
	void updateRight();
	void updateForward();
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
	void setEntityColor(glm::vec3 color);
	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);
	void updateVectors();

	std::string GetName();
	glm::vec3 getScale();
	inline virtual glm::vec3 getColor() const { return glm::vec3(1); };
	inline bool IsLightSource() { return _isLightSource; }
	inline Shader GetShader() { return _entityShader; }
};

#endif // !ENTITY_H

