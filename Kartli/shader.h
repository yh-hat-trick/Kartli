#pragma once
#include "GLEWGLFW.h"
#include <string>

class Shader {

	std::string load(std::string);
public:
	Shader(std::string name);
	void bind();
	~Shader();
	unsigned int shaderID;

	void uniform1f(float x);
	void uniform2f(float x, float y);
	void uniform3f(float x, float y, float z);
};