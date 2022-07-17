#ifndef MODEL_H
#define MODEL_H

#include "entity.h"
#include "mesh.h"
#include "texture_importer.h"
#include "modelimp.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace Engine;

class ENGINE_API Model : public Entity {
private:
	int _width = 0;
	int _height = 0;
	bool _transparency;
	std::vector<Texture> _textures_loaded;
	std::vector<Mesh> _meshes;
	std::string _path;
	Renderer* _renderer = nullptr;
	const char* _modelTexture;
	std::string _directory;
	TextureImporter* _texImporter = NULL;
	Shader _shader;
public:
	Model();
	Model(Renderer* render, Shader shader, std::string path, const char* modelTexture);
	Model(Renderer* render, Shader shader, std::string path);
	~Model();
	void MoveModel(glm::vec3 direction);
	void ScaleModel(float x, float y, float z);
	void RotateModelX(float x);
	void RotateModelY(float y);
	void RotateModelZ(float z);
	//void SetModelPath(string path);
	//void SetTexturePath(const char* texturePath);
	void Draw(Shader& shader);
};

#endif
