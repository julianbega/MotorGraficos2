#include "model.h"

Model::Model() : Entity(_renderer)
{
}

Model::Model(Renderer* render, Shader shader, std::string path, const char* modelTexture) : Entity(render) {
	
	ModelImp::LoadModel(path, _directory, _meshes, _shader, _textures_loaded);
	_modelTexture = modelTexture;
	_shader = shader;
	_name = "modelo";

}

Model::Model(Renderer* render, Shader shader, std::string path) : Entity(render) {
	ModelImp::LoadModel(path, _directory, _meshes, _shader, _textures_loaded);
	_renderer = render;
	_shader = shader;
	_texImporter = new TextureImporter();
}

Model::~Model() {
	if (_texImporter != NULL) {
		delete _texImporter;
		_texImporter = NULL;
	}
}


void Model::MoveModel(glm::vec3 direction) {
	for (int i = 0; i < _meshes.size(); i++) {
		_meshes[i].SetPosition(direction.x, direction.y, direction.z);
	}
}

void Model::ScaleModel(float x, float y, float z) {
	for (int i = 0; i < _meshes.size(); i++) {
		if (x < 0 || y < 0 || z < 0) {
			x = 0; y = 0; z = 0;
		}
		_meshes[i].SetScale(x, y, z);
	}
}

void Model::RotateModelX(float x) {
	for (int i = 0; i < _meshes.size(); i++) {
		_meshes[i].SetXRot(x);
	}
}

void Model::RotateModelY(float y) {
	for (int i = 0; i < _meshes.size(); i++) {
		_meshes[i].SetYRot(y);
	}
}

void Model::RotateModelZ(float z) {
	for (int i = 0; i < _meshes.size(); i++) {
		_meshes[i].SetZRot(z);
	}
}

void Model::Draw(Shader& shader)
{
	updateMatrices();
	updateVectors();
	ModelImp::Draw(shader, _meshes, GetModel());
}
