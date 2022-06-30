#ifndef LIGHT_H
#define LIGHT_H
#include "entity.h"
#include "texture_importer.h"
#include "export.h"

enum type
{
	Directiona, Point, Spotlight
};
class ENGINE_API Light : public Entity {
	Light(Renderer* renderer);
	~Light();


public:
	glm::vec3 position;
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;

	
};

#endif