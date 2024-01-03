#pragma once
#include "Texture.h"

class Framebuffer {
	unsigned int FBO, colorAttachment, depthAttachment, stencilAttachment;


	Framebuffer(int width, int height);
	void bind();
	~Framebuffer();
};