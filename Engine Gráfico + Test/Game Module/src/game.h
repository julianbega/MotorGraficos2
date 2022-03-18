#ifndef GAME_H
#define GAME_H

#include "BaseGame.h"

class Game : public BaseGame {
public:
    Game();
    ~Game();
    float valorRotacion;
	float valorEscala;
	float playerSpeed;
	
	Shape* testShape;
	//Sprite* testSprite;
	//Sprite* testSprite2;
	//Sprite* spriteSheet;
	Animation* playerAnim[8];
    void init() override;
    void updateGame() override;
    void unload() override;
}; 
#endif // !GAME_H