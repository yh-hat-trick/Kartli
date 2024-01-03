#pragma once
#include "Mesh.h"
#include <vector>

class Map {
	//these are things like geometry, props, etc. 
	//the mesh should have geometry data and be renderered by our mesh shader
	//These meshes are more like objects, and this should eventually be replaces with an Entity class or an Object class.
	std::vector<Mesh> meshes;

	//will have things like a skybox object but will not handle rendering of it.

public:
	//should take vertex data and index data from a pointer, load it onto the GPU, and track the VAO and object qualities in the Mesh object.
	void addMesh(Mesh);
};