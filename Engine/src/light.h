#ifndef LIGHT_H
#define LIGHT_H
#include "entity.h"
#include "texture_importer.h"
#include "export.h"


class ENGINE_API Light : public Entity {
	Light(Renderer* renderer);
	~Light();
public:
};

#endif