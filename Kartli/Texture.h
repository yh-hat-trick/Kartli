#pragma once
#include "GLEWGLFW.h"

class Texture
{
	int width, height, nrChannels;
	unsigned int textureID;
public:
	Texture(const char* path);
	Texture();
	~Texture();
	void bind(GLenum type);
};