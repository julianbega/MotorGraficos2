#ifndef SHAPE_H
#define SHAPE_H
#include "export.h"
#include "renderer.h"
#include "entity.h"
#include "dataManager.h"
#include "global_declarations.h"


enum class ENGINE_API Type {
    quad, tri, cube, normalCube
};


class ENGINE_API Shape : public Entity{
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;

    float quadVertices[24] = {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f   // top left 
    };
    unsigned int quadIndices[6] = {
        0,1,3,
        1,2,3
    };
    float triangleVertices[18] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
    };
    unsigned int triangleIndices[3] = {
        0, 1, 2
    };
	float cubeVertices[48] = {
			-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f,
			-1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f,
			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f
	};
	float cubeVerticesNormal[324] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, -1.0f,//0
			 0.5f, -0.5f, -0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, -1.0f,//1
			 0.5f,  0.5f, -0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, -1.0f,//2
			 0.5f,  0.5f, -0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, -1.0f,//3
			-0.5f,  0.5f, -0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, -1.0f,//4
			-0.5f, -0.5f, -0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, -1.0f,//5

			-0.5f, -0.5f,  0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, 1.0f,//6
			 0.5f, -0.5f,  0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, 1.0f,//7
			 0.5f,  0.5f,  0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, 1.0f,//8
			 0.5f,  0.5f,  0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, 1.0f,//9
			-0.5f,  0.5f,  0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, 1.0f,//10
			-0.5f, -0.5f,  0.5f,  0.0f, 0.25f, 0.0f,  0.0f, 0.0f, 1.0f,//11

			-0.5f,  0.5f,  0.5f,  0.0f, 0.25f, 0.0f, -1.0f,  0.0f,  0.0f,//12
			-0.5f,  0.5f, -0.5f,  0.0f, 0.25f, 0.0f, -1.0f,  0.0f,  0.0f,//13
			-0.5f, -0.5f, -0.5f,  0.0f, 0.25f, 0.0f, -1.0f,  0.0f,  0.0f,//14
			-0.5f, -0.5f, -0.5f,  0.0f, 0.25f, 0.0f, -1.0f,  0.0f,  0.0f,//15
			-0.5f, -0.5f,  0.5f,  0.0f, 0.25f, 0.0f, -1.0f,  0.0f,  0.0f,//16
			-0.5f,  0.5f,  0.5f,  0.0f, 0.25f, 0.0f, -1.0f,  0.0f,  0.0f,//17
			
			 0.5f,  0.5f,  0.5f,  0.0f, 0.25f, 0.0f, 1.0f,  0.0f,  0.0f,//18
			 0.5f,  0.5f, -0.5f,  0.0f, 0.25f, 0.0f, 1.0f,  0.0f,  0.0f,//19
			 0.5f, -0.5f, -0.5f,  0.0f, 0.25f, 0.0f, 1.0f,  0.0f,  0.0f,//20
			 0.5f, -0.5f, -0.5f,  0.0f, 0.25f, 0.0f, 1.0f,  0.0f,  0.0f,//21
			 0.5f, -0.5f,  0.5f,  0.0f, 0.25f, 0.0f, 1.0f,  0.0f,  0.0f,//22
			 0.5f,  0.5f,  0.5f,  0.0f, 0.25f, 0.0f, 1.0f,  0.0f,  0.0f,//23

			-0.5f, -0.5f, -0.5f,  0.0f, 0.25f, 0.0f, 0.0f, -1.0f,  0.0f,//24
			 0.5f, -0.5f, -0.5f,  0.0f, 0.25f, 0.0f, 0.0f, -1.0f,  0.0f,//25
			 0.5f, -0.5f,  0.5f,  0.0f, 0.25f, 0.0f, 0.0f, -1.0f,  0.0f,//26
			 0.5f, -0.5f,  0.5f,  0.0f, 0.25f, 0.0f, 0.0f, -1.0f,  0.0f,//27
			-0.5f, -0.5f,  0.5f,  0.0f, 0.25f, 0.0f, 0.0f, -1.0f,  0.0f,//28
			-0.5f, -0.5f, -0.5f,  0.0f, 0.25f, 0.0f, 0.0f, -1.0f,  0.0f,//29

			-0.5f,  0.5f, -0.5f,  0.0f, 0.25f, 0.0f, 0.0f,  1.0f,  0.0f,//30
			 0.5f,  0.5f, -0.5f,  0.0f, 0.25f, 0.0f, 0.0f,  1.0f,  0.0f,//31
			 0.5f,  0.5f,  0.5f,  0.0f, 0.25f, 0.0f, 0.0f,  1.0f,  0.0f,//32
			 0.5f,  0.5f,  0.5f,  0.0f, 0.25f, 0.0f, 0.0f,  1.0f,  0.0f,//33
			-0.5f,  0.5f,  0.5f,  0.0f, 0.25f, 0.0f, 0.0f,  1.0f,  0.0f,//34
			-0.5f,  0.5f, -0.5f,  0.0f, 0.25f, 0.0f, 0.0f,  1.0f,  0.0f//35
	};
	unsigned int cubeIndices[36] = {
			0,1,2,
			2,3,0,
			1,5,6,
			6,2,1,
			7,6,5,
			5,4,7,
			4,0,3,
			3,7,4,
			4,5,1,
			1,0,4,
			3,2,6,
			6,7,3
	};
	unsigned int cubeIndicesNormal[36] = {
			0,1,2,
			3,4,5,
			6,7,8,
			9,10,11,
			12,13,14,
			15,16,17,
			18,19,20,
			21,22,23,
			24,25,26,
			27,28,29,
			30,31,32,
			33,34,35
	};

    Type shape;
    Shader _shader;
	Material _material;
	float parameterType;
    void generateVAO();

    void bindVAO();
    void bindVBO();
    void bindEBO();
	void setters();

    void bindBuffers(float* quadVertex, float* triVertex, int quadVertexSize, int triVertexSize);

    void clearBuffers();

public:

    Shape(Type type, Renderer* renderer, Shader& shader, std::string name);
    ~Shape();

    void initShape();

    void setColor(float r, float g, float b);
	void setMaterial(vec3 ambient, vec3 diffuse, vec3 specular, float shininess);
	void setMaterial(Material mat);

    void draw();
};


#endif // !SHAPE_H

