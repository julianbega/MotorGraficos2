#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include "export.h"
#include <string>

class ENGINE_API TextureImporter {
	const char* _path;
	unsigned char* _data;
	unsigned int _texture;
	int nrChannels;
public:
	TextureImporter();
	TextureImporter(const char* path);
	TextureImporter(int width, int height, const char* path, bool transparency);
	~TextureImporter();
	void LoadImage(int width, int height, bool transparency);
	void SetPath(const char* path);
	const char* GetPath();
	unsigned int GetTexture();
	unsigned int loadTexture(const char* path, int width, int height, bool transparency);
	unsigned int textureFromFile(const char* path, const std::string& directory, bool gamma);
};

#endif // !TEXTURE_IMPORTER_H

