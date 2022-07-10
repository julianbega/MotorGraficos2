#ifndef LIGHT_H
#define LIGHT_H
#include "export.h"
#include <glm.hpp>
#include <iostream>
#include "entity.h"


class Renderer;
class TextureImporter;
class Shader;

enum lightType
{
	Directional, Point, Spotlight
};
class ENGINE_API Light : public Entity {
	lightType type;
	Renderer* _renderer;
	TextureImporter* _texImporter;
	Shader shader;
	glm::vec3 color;
	unsigned int _vbo = 0;
	unsigned int _vao = 0;
	unsigned int _ebo = 0;
	int pointLightId;
	int spotLightId;
	static int nextPointLightId;
	static int nextspotLightId;

	unsigned int diffuse;
	unsigned int specular;

	void loadBaseSprite();
	void bindBuffers();


	float vertices[264] = {
		0.5f,  0.5f, 0.5f,   1.f, 1.f, 1.f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
	   -0.5f, -0.5f, 0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	   -0.5f,  0.5f, 0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

		 0.5f, -0.5f,  0.5f,  1.f, 1.f, 1.f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

		 0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   -1.0f, 0.0f, 0.0,   1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.f, 1.f, 1.f,   -1.0f, 0.0f, 0.0,   1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f,   -1.0f, 0.0f, 0.0,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,   -1.0f, 0.0f, 0.0,   0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f,   0.0f, 1.0f, 0.0,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f,   0.0f, 1.0f, 0.0,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 1.0f, 0.0,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, 1.0f, 0.0,   0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  1.f, 1.f, 1.f,   0.0f, -1.0f, 0.0,   1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.f, 1.f, 1.f,   0.0f, -1.0f, 0.0,   1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, -1.0f, 0.0,   0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,   0.0f, -1.0f, 0.0,   0.0f, 1.0f
	};

	unsigned int indices[36] = {
		0, 1, 3,
		1, 2, 3,
		4, 5, 7,
		5, 6, 7,
		8, 9, 11,
		9, 10, 11,
		12, 13, 15,
		13, 14, 15,
		16, 17, 19,
		17, 18, 19,
		20, 21, 23,
		21, 22, 23
	};


public:
	Light(Renderer* renderer, Shader& shader, lightType type, std::string lightName);
	~Light();

	void init();
	virtual void setColor(glm::vec3 color);
	virtual void setColor(float r, float g, float b);

	void draw();

	virtual glm::vec3 getColor() const { return color;}
	
};

#endif