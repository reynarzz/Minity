#pragma once
#include <string>
#include <gl/glew.h>

using std::string;

class Texture
{
private:
	unsigned int _rendererID;
	string _filePath;
	unsigned char* _textureBuffer;
	int _width, _height, _bitsperpixel;
	bool _binded;
public:
	Texture(const string& path);
	~Texture();

	void Bind(unsigned int slot);
	void Unbind() const;

	inline int GetWidth() const;
	inline int GetHeight() const;
};

