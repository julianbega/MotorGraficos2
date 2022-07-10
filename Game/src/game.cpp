#include "game.h"
#include <windows.data.json.h>

Game::Game() : Gamebase(){
}
	
Game::~Game() {
	if (cube) delete cube; 
	if (directional) delete directional;
	if (spot) delete spot;
	if (point) delete point;
}

	//initialization of game variables
void Game::Init() {
	lastX = window->getWidth() / 2;
	lastY = window->getHeight() / 2;

	cube = new Cube(renderer, basicShader, "cube");
	cube->init("Game/res/textures/Solid_red.png", "Game/res/textures/Solid_red.png");
	cube->SetPosition(0, -0.5f, -1.f);
	cube->SetScale(5, .1f, 5);


	directional = new Light(renderer, basicShader, lightType::Directional, "Directional");
	directional->init();
	directional->show(false);
	directional->SetPosition(.5f, .5f, -3.f);
	directional->transform.rotation.y = 90;
	directional->transform.rotation.x = -45;
	directional->SetScale(.1f, .1f, .1f);
	directional->setColor(1, 1, 1);

	spot = new Light(renderer, basicShader, lightType::Spotlight, "Spotlight");
	spot->init();
	spot->SetPosition(.5f, .5f, -1.f);
	spot->transform.rotation.y = 90;
	spot->SetScale(.1f, .1f, .1f);
	spot->setColor(1, 1, 1);

	point = new Light(renderer, basicShader, lightType::Point, "Point");
	point->init();
	point->SetPosition(1, .5f, -1.f);
	point->SetScale(.1f, .1f, .1f);
	point->setColor(1, 1, 1);
}

void Game::Update() {

	Inputs();
	cube->draw();
	directional->draw();
	spot->draw();
	point->draw();
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
	if (directional) {
		delete directional;
		directional = NULL;
	}
	if (spot) {
		delete spot;
		spot = NULL;
	}
	if (point) {
		delete point;
		point = NULL;
	}
}

