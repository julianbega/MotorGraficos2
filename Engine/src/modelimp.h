#ifndef MODELIMP_H
#define MODELIMP_H

#include <glm.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.h"
#include "mesh.h"
#include "entity.h"
#include "time_manager.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "texture_importer.h"


namespace Engine {
	class ENGINE_API ModelImp : public Entity{
	private:
		int _width = 0;
		int _height = 0;
		bool _transparency;
		std::vector<Texture> _textures_loaded;
		std::vector<Mesh> _meshes;
		std::string _path;
		Renderer *_renderer = nullptr;
		const char* _modelTexture;
		std::string _directory;
		//const string* _modelTexture;
		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

		TextureImporter* _texImporter = NULL;

		Shader _shader;

		unsigned int TextureFromFile(const char* path, const std::string &directory,bool gamma);
		void LoadTexture();
		unsigned int TextureModel(const char* texture);
	public:
		ModelImp();
		ModelImp(Renderer* render, Shader shader, std::string path, const char* modelTexture);
		ModelImp(Renderer* render, Shader shader, std::string path);
		~ModelImp();
		void MoveModel(glm::vec3 direction);
		void ScaleModel(float x, float y, float z);
		void RotateModelX(float x);
		void RotateModelY(float y);
		void RotateModelZ(float z);
		//void SetModelPath(string path);
		//void SetTexturePath(const char* texturePath);
		void Draw(Shader& shader);
	};
}

#endif