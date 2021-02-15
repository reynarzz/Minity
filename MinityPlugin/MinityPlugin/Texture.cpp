#include "pch.h"


#include "Texture.h"
#include "Dependencies/image/stb_image.h"
bool binded = false;

Texture::Texture(const string& path) :
	_rendererID(0), _filePath(path), _textureBuffer(nullptr), _width(0), _height(0), _bitsperpixel(0)
{

	stbi_set_flip_vertically_on_load(1);
	_textureBuffer = stbi_load(path.c_str(), &_width, &_height, &_bitsperpixel, 4);


	glGenTextures(1, &_rendererID);
	glBindTexture(GL_TEXTURE_2D, _rendererID);

	// loading image is in scaline way (top from bottom), but open gl {0,0} is bottom left
	/*stbi_set_flip_vertically_on_load(1);
	_textureBuffer = stbi_load(path.c_str(), &_width, &_height, &_bitsperpixel, 4);*/

	//---stbi_load_16_from_memory(&imageBuffer,) 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _textureBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (_textureBuffer)
	{
		stbi_image_free(_textureBuffer);
	}
}

void Texture::Bind(unsigned int slot)
{
	//glActiveTexture(GL_TEXTURE_2D + slot);

	glBindTexture(GL_TEXTURE_2D, _rendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

inline int Texture::GetWidth() const
{
	return _width;
}

inline int Texture::GetHeight() const
{
	return _height;
}

Texture::~Texture()
{
	glDeleteTextures(1, &_rendererID);
}
