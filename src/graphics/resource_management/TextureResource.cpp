#include <graphics/resource_management/TextureResource.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

TextureResource::TextureResource()
	: id(0)
{
}

TextureResource::~TextureResource()
{
	if (id) {
		glDeleteTextures(1, &id);
		id = 0;
	}
}

void TextureResource::init()
{
	glGenTextures(1, &id);
}