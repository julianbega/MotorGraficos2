#ifndef GAME_H
#define GAME_H
#include "gamebase.h"
#include "glm.hpp"

class Game : public Gamebase{

	float timer = 0;
	float speed = 1;
	float rotationSpeed = 100;
	Cube* cube;
	float lastX;
	float lastY;
	bool firstMouse = true;
	float xPosIn = 0;
	float yPosIn = 0;
public:
	Game();
	~Game();
	void Inputs();
	void Init() override;
	void Update() override;
	void Unload() override;
};

#endif // !GAME_H

