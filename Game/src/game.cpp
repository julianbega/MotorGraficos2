#include "game.h"
#include <windows.data.json.h>

Game::Game() : Gamebase(){
}
	
Game::~Game() {
	if (triangle) delete triangle;
	if (square2) delete square2;
	if (sprite1) delete sprite1;
	if (player) delete player;
	if (idle) delete idle;
}

	//initialization of game variables
void Game::Init() {
	lastX = window->getWidth() / 2;
	lastY = window->getHeight() / 2;
	triangle = new Shape(Type::tri, renderer, basicShader, "Triangle1");
	square2 = new Shape(Type::quad, renderer, basicShader,"Square2");
	sprite1 = new Sprite(true, "res/textures/granadeIcon.png", renderer, textureShader, "Sprite1");
	player = new Sprite(true, "res/textures/PlayerShit.png", renderer, textureShader, "Player");

	triangle->initShape();
	triangle->SetPosition(.5f, .1f, -1.f);
	triangle->SetScale(.5f, .5f, 1.f);
	square2->setColor(0.0f, 1.0f, 1.0f);

	square2->initShape();
	square2->SetPosition(1.0f, 0.5f, 0.0f);
	square2->SetScale(0.4f, 0.4f, 0.5f);
	square2->setColor(0.0f, 0.0f, 1.0f);

	sprite1->init();
	sprite1->SetPosition(.1f, .5f, -1.f);
	sprite1->SetScale(.25f, .25f, 0.5f);
	sprite1->setColor(1.0f, 1.0f, 1.0f);


}

	//game update
void Game::Update() {
	//input
	Inputs();

	//update

	timer += time.getDeltaTime();

	//draw
	triangle->draw();
	square2->draw();
	sprite1->draw();
	
	//std::cout << "fps: " << time.getFPS() << "\n";
}

void Game::Inputs() {
	// add inputs here
	camera->inputs(input, time);	


	if (input.getKey(keyCode::W)) {
		camera->transform.position += camera->getForward() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::S)) {
		camera->transform.position -= camera->getForward() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::A)) {
		camera->transform.position -= camera->getRight() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::D)) {
		camera->transform.position += camera->getRight() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::RIGHT)) {
		camera->rotationSpeed = rotationSpeed * time.getDeltaTime();
		camera->rotateYaw(camera->rotationSpeed);
	}
	if (input.getKey(keyCode::LEFT)) {
		camera->rotationSpeed = rotationSpeed * time.getDeltaTime();
		camera->rotateYaw(-camera->rotationSpeed);
	}
	if (input.getKey(keyCode::UP)) {
		camera->rotationSpeed = rotationSpeed * time.getDeltaTime();
		camera->rotatePitch(camera->rotationSpeed);
	}
	if (input.getKey(keyCode::DOWN)) {
		camera->rotationSpeed = rotationSpeed * time.getDeltaTime();
		camera->rotatePitch(-camera->rotationSpeed);
	}
}

	// free memory
void Game::Unload() {
	dataManager->clearLevelEntities();
	if (triangle) {
		delete triangle;
		triangle = NULL;
	}
	if (square2) {
		delete square2;
		square2 = NULL;
	}
	if (sprite1) {
		delete sprite1;
		sprite1 = NULL;
	}
	if (player){
		delete player;
		player = NULL;
	}
	if (idle) {
		delete idle;
		idle = NULL;
	}
}

