#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Export.h"
#include "Entity2D.h"
#include "glm/glm.hpp"

class ENGINE_API CollisionManager {
public:
	enum class sides { top = 0, bottom, right, left, none };

	CollisionManager();
	
	bool CheckAABBCollisions(Entity2D* one, Entity2D* two, float playerSpeed);
	sides CheckOverlapCollisions(Entity2D* one, Entity2D* two);
	void MovePlayer(Entity2D* player, Entity2D* object, float playerSpeed);
	void MoveObject(Entity2D* player, Entity2D* object, float playerSpeed);

private:
	bool ReturnIntersect(float min0,float max0,float min1,float max1);
	float GetOverlap(Entity2D* player, Entity2D* object);
};
#endif // !CAMERA_H