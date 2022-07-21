#ifndef MESH_H
#define MESH_H

#include <glm.hpp>

#include "shader.h"
#include "entity.h"
#include "renderer.h"

#include <vector>
#include <string>

#include "export.h"

namespace Engine {
	struct ENGINE_API Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Color;
		glm::vec2 TexCoords;

	};
	
	struct ENGINE_API Texture {
		unsigned int id;
		std::string type;
		std::string path;
	};

	class ENGINE_API Mesh : public Entity {
	private:
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;
		unsigned int _positionAttrib;
		unsigned int _normalAttrib;
		unsigned int _textureAttrib;
		unsigned int _colorAttrib;
		Shader _shader;
		void SetUpMesh();
		void bindTextures(Shader& shader);
		Renderer *_renderer;
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Shader shader);
		~Mesh();
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		void Draw(Shader& shader, glm::mat4 mvp);
	};
}

#endif