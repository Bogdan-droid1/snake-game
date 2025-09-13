#pragma once
#include <glad/glad.h>
#include <iostream>


class Texture
{
public:
	Texture() = default;
	Texture(const char* texPath, GLint rgb_or_rgba);
	~Texture();
	void Init(const char* texPath, GLint rgb_or_rgba);

private:
	static uint16_t nrOfTextures;
	unsigned int m_ID;
	int m_width;
	int m_height;
	int m_nrChannels;
};
