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
	static class ENGINE_API ModelImp{	
	public:
		ModelImp();
		~ModelImp();
		static void LoadModel(std::string path, std::string& _directory, std::vector<Mesh>& _meshes, Shader& _shader, std::vector<Texture>& _textures_loaded);
		static void ProcessNode(aiNode* node, const aiScene* scene, std::string& _directory, std::vector<Mesh>& _meshes, Shader& _shader, std::vector<Texture>& _textures_loaded);
		static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, std::string& _directory, Shader& _shader, std::vector<Texture>& _textures_loaded);
		static std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, std::string& _directory, std::vector<Texture>& _textures_loaded);
		static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
		static void Draw(Shader& shader, std::vector<Mesh>& _meshes, glm::mat4 mvp);
	};
}

#endif