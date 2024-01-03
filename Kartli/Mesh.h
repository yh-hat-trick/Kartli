#pragma once
#include "glm/glm.hpp"

//Mesh
struct Mesh
{
	//should contain data unique to each mesh
	glm::mat4 pos = glm::mat4(1.0f);
	unsigned int vao, vbo, ebo;

};