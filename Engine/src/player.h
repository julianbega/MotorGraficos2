#ifndef PLAYER_H
#define PLAYER_H
#include "export.h"
#include "entity.h"
#include "camera.h"

class ENGINE_API Player : public Entity {
protected:
	
public:
	Camera camera;
	
};


#endif