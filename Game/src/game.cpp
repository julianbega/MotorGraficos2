#include "game.h"
#include <windows.data.json.h>

Game::Game() : Gamebase(){
}
	
Game::~Game() {
	if (cube) delete cube;
	if (spot) delete spot;
	if (point) delete point;
	if (point) delete point2;
	if (model) delete model;
}

	//initialization of game variables
void Game::Init() {
	lastX = window->getWidth() / 2;
	lastY = window->getHeight() / 2;

	cube = new Cube(renderer, standardShader, "cube");
	cube->init("res/textures/container2.png", "res/textures/container2_specular.png");
	cube->SetPosition(0, .5f, -1.f);
	cube->SetScale(.25f, .25f, .25f);

	spot = new LightSource(renderer, standardShader, LightType::SpotLight, "spot");
	spot->init();
	spot->SetPosition(.5f, .5f, -1.f);
	spot->SetYRot(-90);
	spot->SetScale(.1f, .1f, .1f);
	spot->setColor(1, 1, 1);

	point = new LightSource(renderer, standardShader, LightType::PointLight, "point");
	point->init();
	point->SetPosition(-.5f, .5f, 0.25f);
	point->SetYRot(-90);
	point->SetScale(.1f, .1f, .1f);
	point->setColor(0.2f, 0.2f, 1);
	//point->

	point2 = new LightSource(renderer, standardShader, LightType::PointLight, "point2");
	point2->init();
	point2->SetPosition(0.5f, .5f, 0.25f);
	point2->SetYRot(-90);
	point2->SetScale(.1f, .1f, .1f);
	point2->setColor(1, 0.2f, 0.2f);

	model = new Model(renderer, standardShader, "res/models/cyborg/cyborg.obj");
	model->SetPosition(0.0f, 0.0f, 0.0f);
	model->SetScale(0.25f, 0.25f, 0.25f);
}

	//game update
void Game::Update() {
	//input
	Inputs();


	timer += time.getDeltaTime();

	//draw
	point->draw();
	point2->draw();
	spot->draw();
	cube->draw();
	model->Draw(standardShader);
	//std::cout << "fps: " << time.getFPS() << "\n";
}

void Game::Inputs() {
	// add inputs here

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
	if (input.getKey(keyCode::Q)) {
		camera->transform.position -= camera->getUp() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::E)) {
		camera->transform.position += camera->getUp() * (speed * time.getDeltaTime());
	}
	if (input.getKey(keyCode::P)) {
		point->isActive = !point->isActive;
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
	if (input.getKey(keyCode::R)) {
		model->SetScale(model->getScale().x + 0.01f, model->getScale().y + 0.01f, model->getScale().z + 0.01f);		
	}
	if (input.getKey(keyCode::T)) {
		model->SetScale(model->getScale().x - 0.01f, model->getScale().y - 0.01f, model->getScale().z - 0.01f);
	}
	if (input.getKey(keyCode::F)) {
		model->SetYRot(model->transform.rotation.y - 1.0f);
	}
	if (input.getKey(keyCode::G)) {
		model->SetYRot(model->transform.rotation.y + 1.0f);
	}
	if (input.getKey(keyCode::V)) {
		model->SetPosition(model->transform.position.x - 0.01f, model->transform.position.y - 0.01f, model->transform.position.z - 0.01f);
	}
	if (input.getKey(keyCode::B)) {
		model->SetPosition(model->transform.position.x + 0.01f, model->transform.position.y + 0.01f, model->transform.position.z + 0.01f);
	}
}

	// free memory
void Game::Unload() {
	dataManager->clearLevelEntities();
	if (cube) {
		delete cube;
		cube = NULL;
	}
	if (spot) {
		delete spot;
		spot = NULL;
	}
	if (point) {
		delete point;
		point = NULL;
	}
	if (point2) {
		delete point2;
		point2 = NULL;
	}
	if (model) {
		delete model;
		model = NULL;
	}
}

