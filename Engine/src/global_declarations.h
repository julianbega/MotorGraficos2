#ifndef GLOBAL_DECLARATIONS_H
#define GLOBAL_DECLARATIONS_H

struct vec3
{
	float x;
	float y;
	float z;
};
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

#endif