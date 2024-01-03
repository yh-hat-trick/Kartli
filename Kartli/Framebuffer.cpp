#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, int height)
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	//attach a color buffer
	glGenTextures(1, &colorAttachment);
	glBindTexture(GL_TEXTURE_2D, colorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

Framebuffer::~Framebuffer()
{

}