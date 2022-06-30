#include "game.h"
#include <windows.data.json.h>

Game::Game() : Gamebase(){
}
	
Game::~Game() {
	if (cube) delete cube;
}

	//initialization of game variables
void Game::Init() {
	lastX = window->getWidth() / 2;
	lastY = window->getHeight() / 2;


	cube = new Cube(renderer, basicShader, "cube");
	cube->init("res/textures/wood.png", "res/textures/wood.png");
	cube->SetPosition(0, -0.5f, -1.f);
	cube->SetScale(5, .1f, 5);
}

void Game::Update() {

	Inputs();
	cube->draw();
	timer += time.getDeltaTime();
	//std::cout << "fps: " << time.getFPS() << "\n";
}

void Game::Inputs() {
	// add inputs here
	camera->inputs(input, time);	

	
}

	// free memory
void Game::Unload() {

	dataManager->clearLevelEntities();	
	if (cube) {
		delete cube;
		cube = NULL;
	}
}

